#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/epoll.h>

#define TTY9	"/dev/tty9"
#define TTY10	"/dev/tty10"

#define BUFSIZE	1024

enum {
	S_READ=1,
	S_WRITE,
	S_EXCEPTION,
	S_TERM
};

// 抽象数据类型
typedef struct {
	int rfd;
	int wfd;
	int state;
	char buf[BUFSIZE];
	int readcnt;
	char *errfun;
}fsm_t;

static fsm_t *fsm_init(int rfd, int wfd)
{
	int rfd_save;
	int wfd_save;

	fsm_t *f = malloc(sizeof(fsm_t));
	if (NULL == f)
		return NULL;
	// 确保rfd, wfd一定值非阻塞
	rfd_save = fcntl(rfd, F_GETFL);
	fcntl(rfd, F_SETFL, rfd_save | O_NONBLOCK);
	wfd_save = fcntl(wfd, F_GETFL);
	fcntl(wfd, F_SETFL, wfd_save | O_NONBLOCK);

	f->rfd = rfd;
	f->wfd = wfd;
	f->state = S_READ;
	memset(f->buf, '\0', BUFSIZE);
	f->readcnt = 0;
	f->errfun = NULL;

	return f;
}

// 推动状态机运行
int fsm_drive(fsm_t *fsm)
{
	switch (fsm->state) {
		case S_READ:
			fsm->readcnt = read(fsm->rfd, fsm->buf, BUFSIZE);
			if (fsm->readcnt == -1) {
				if (errno != EAGAIN) {
					fsm->errfun = "read()";
					fsm->state = S_EXCEPTION;
				}
			} else if (fsm->readcnt == 0) {
				fsm->state = S_TERM;
			} else {
				fsm->state = S_WRITE;
			}
			break;
		case S_WRITE:
			if (write(fsm->wfd, fsm->buf, fsm->readcnt) == -1) {
				fsm->errfun = "write()";	
				fsm->state = S_EXCEPTION;
			} else {
				fsm->state = S_READ;
				memset(fsm->buf, '\0', BUFSIZE);
				fsm->readcnt = 0;
			}
			break;
		case S_EXCEPTION:
			perror(fsm->errfun);
			// abort();
			fsm->state = S_TERM;
			break;
		case S_TERM:
			break;
		default:
			break;
	}
}

int main(void)
{
	int fd1, fd2;
	fsm_t *fsm12, *fsm21;
	int epfd;
	struct epoll_event evt, revt;

	fd1 = open(TTY9, O_RDWR | O_NONBLOCK);
	if (-1 == fd1) {
		perror("open()");
		exit(1);
	}

	fd2 = open(TTY10, O_RDWR);
	if (-1 == fd2) {
		perror("open()");
		goto ERROR;
	}

	fsm12 = fsm_init(fd1, fd2);
	fsm21 = fsm_init(fd2, fd1);

	// 
	epfd = epoll_create(1);
	if (epfd == -1) {
		perror("epoll_create()");
		goto ERROR2;
	}

	// 添加文件描述符
	evt.events = 0;
	evt.data.fd = fd1;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd1, &evt);
	evt.events = 0;
	evt.data.fd = fd2;
	epoll_ctl(epfd, EPOLL_CTL_ADD, fd2, &evt);

	//推动状态机--->通知法 select
	while (1) {
		if (fsm12->state == S_TERM && fsm21->state == S_TERM)
			break;

		if (fsm12->state == S_EXCEPTION) {
			fsm_drive(fsm12);
			continue;
		}
		if (fsm21->state == S_EXCEPTION) {
			fsm_drive(fsm21);
			continue;
		}

		evt.events = 0;
		evt.data.fd = fd1;
		if (fsm12->state == S_READ) {
			evt.events |= EPOLLIN;
		}
		if (fsm21->state == S_WRITE) {
			evt.events |= EPOLLOUT;
		}
		epoll_ctl(epfd, EPOLL_CTL_MOD, fd1, &evt);
	
		evt.events = 0;
		evt.data.fd = fd2;
		if (fsm21->state == S_READ)
			evt.events |= EPOLLIN;
		if (fsm12->state == S_WRITE)
			evt.events |= EPOLLOUT;
		epoll_ctl(epfd, EPOLL_CTL_MOD, fd2, &evt);

		if (epoll_wait(epfd, &revt, 1, -1) == -1) {
			perror("epoll_wait()");
			goto ERROR2;
		}

		if ((revt.events & EPOLLIN && revt.data.fd == fd1) || \
				(revt.events & EPOLLOUT && revt.data.fd == fd2))
			fsm_drive(fsm12);	
		if ((revt.events & EPOLLIN && revt.data.fd == fd2) || \
				(revt.events & EPOLLOUT && revt.data.fd == fd1))
			fsm_drive(fsm21);	
	}

	close(epfd);

	close(fd1);
	close(fd2);

	exit(0);
ERROR2:
	close(fd2);
ERROR:
	close(fd1);
	exit(1);
}


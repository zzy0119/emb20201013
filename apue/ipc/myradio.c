#include <stdio.h>
#include <time.h>
#include <errno.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE		1024
#define MUSICFILE	"/home/emb1013/桌面/truth.mp3"

int main(int argc, char *argv[])
{
	int pfd[2] = {};
	pid_t pid;
	int fd;
	int cnt;
	char buf[BUFSIZE] = {};

	if (pipe(pfd) == -1) {
		perror("pipe()");
		exit(1);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		goto ERROR;
	}

	if (pid == 0) {
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		execlp("mplayer", "mplayer", "-", NULL);
		perror("execlp()");
		exit(1);
	}

	fd = open(MUSICFILE, O_RDONLY);
	if (fd == -1) {
		perror("open()");
		goto ERROR;	
	}
	close(pfd[0]);

	struct timespec tm;

	tm.tv_sec = 0;
	tm.tv_nsec = 300000000;

	while (1) {
		cnt = read(fd, buf, BUFSIZE);
		if (cnt == 0)
			break;
		if (cnt == -1) {
			if (errno == EINTR)
				continue;
			perror("read()");
			exit(1);
		}
		write(pfd[1], buf, cnt);
		nanosleep(&tm, NULL);
	}
	close(pfd[1]);
	close(fd);
	wait(NULL);

	exit(0);
ERROR:
	close(pfd[0]);
	close(pfd[1]);
	exit(1);
}


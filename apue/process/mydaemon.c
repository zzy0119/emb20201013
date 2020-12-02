#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>

#define BUFSIZE	 	100 
#define FLNAME		"/tmp/out"
#define RIDFL		"/dev/null"
#define LOCKFILE	"/var/run/mydaemon.pid"

int mydaemon();
int already_running();
int main(void)
{
	struct tm *tmp;
	time_t tm;
	char buf[BUFSIZE] = {};
	FILE *fp = NULL;

	// 守护进程
#if 0
	if (mydaemon() == -1) {
		exit(1);
	}
#endif
	if (daemon(0, 0) == -1)
		exit(1);
	if (already_running() == -1) {
		syslog(LOG_ERR, "already_running() failed");
		exit(1);
	}

	openlog("./mydaemon", LOG_PID | LOG_PERROR, LOG_DAEMON);

	fp = fopen(FLNAME, "w");
	if (NULL == fp) {
		// perror("fopen()");
		syslog(LOG_ERR, "fopen():%s", strerror(errno));
		exit(1);
	}

	while (1) {
		time(&tm);	
		tmp = localtime(&tm);
		// if error
		strftime(buf, BUFSIZE, "%Y-%m-%d %H:%M:%S\n", tmp);	
		fputs(buf, fp);	
		fflush(NULL);
		// syslog(LOG_INFO, "%s write into file", buf);
		sleep(1);
	}

	fclose(fp);
	closelog();

	exit(0);
}
 
int mydaemon()
{
	pid_t pid;
	int fd;

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		return -1;
	}
	if (pid > 0) {
		exit(0);
	}
	if (setsid() == -1) {
	// 	perror("setsid()");
		syslog(LOG_ERR, "setsid():%s", strerror(errno));
		return -1;
	}
	// 重定向0, 1, 2
	fd = open(RIDFL, O_RDWR);
	if (fd == -1) {
		// perror("open()");
		syslog(LOG_ERR, "open():%s", strerror(errno));
		return -1;
	}
	dup2(fd, 0);
	dup2(fd, 1);
	dup2(fd, 2);
	if (fd > 2)
		close(fd);

	// 设置文件屏蔽字
	umask(0);
	// 切换工作目录
	chdir("/");

	return 0;
}

// 单实例
int already_running()
{
	int fd;
	char buf[BUFSIZE] = {};

	fd = open(LOCKFILE, O_WRONLY | O_CREAT, 0666);	
	if (fd == -1) {
		syslog(LOG_ERR, "open():%s", strerror(errno));
		return -1;
	}

	if (lockf(fd, F_TLOCK, 0) == -1) {
		syslog(LOG_ERR, "lockf():%s", strerror(errno));
		close(fd);
		return -1;
	}
	syslog(LOG_DEBUG, "pid:%d\n", getpid());
	ftruncate(fd, 0);
	snprintf(buf, BUFSIZE, "%d", getpid());
	write(fd, buf, strlen(buf));
	// close(fd);
	return 0;
}






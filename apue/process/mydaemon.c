#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define BUFSIZE	 	100 
#define FLNAME		"/tmp/out"
#define RIDFL		"/dev/null"

int mydaemon();
int main(void)
{
	struct tm *tmp;
	time_t tm;
	char buf[BUFSIZE] = {};
	FILE *fp = NULL;

	// 守护进程
	if (mydaemon() == -1) {
		exit(1);
	}

	fp = fopen(FLNAME, "w");
	if (NULL == fp) {
		perror("fopen()");
		exit(1);
	}

	while (1) {
		time(&tm);	
		tmp = localtime(&tm);
		// if error
		strftime(buf, BUFSIZE, "%Y-%m-%d %H:%M:%S\n", tmp);	
		fputs(buf, fp);	
		fflush(NULL);
		sleep(1);
	}

	fclose(fp);

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
		perror("setsid()");
		return -1;
	}
	// 重定向0, 1, 2
	fd = open(RIDFL, O_RDWR);
	if (fd == -1) {
		perror("open()");
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





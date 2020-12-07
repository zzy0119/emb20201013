#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#define BUFSIZE 1024

int cpfile(int rfd, int wfd)
{
	char buf[BUFSIZE] = {};
	int cnt;

	while (1) {
		cnt = read(rfd, buf, BUFSIZE);
		if (cnt == 0)
			break;
		if (cnt == -1) {
			if (errno == EINTR)
				continue;
			perror("read()");
			return -1;
		}
		write(wfd, buf, cnt);
	}
}

int main(int argc, char *argv[])
{
	int pfd[2] = {};
	pid_t pid;	
	int fd;

	if (argc < 2)
		exit(1);

	if (pipe(pfd) == -1) {
		perror("pipe()");
		exit(1);
	}
	pid = fork();
	if (pid < 0) {
		perror("fork()");
		goto ERROR;
	}
	if (pid == 0) {
		close(pfd[1]);
		cpfile(pfd[0], 1);
		close(pfd[0]);
		exit(1);
	}

	close(pfd[0]);
	fd = open(argv[1], O_RDONLY);
	// if error
	cpfile(fd, pfd[1]);
	close(pfd[1]);
	close(fd);

	wait(NULL);

	return 0;
ERROR:
	close(pfd[0]);
	close(pfd[1]);
	exit(1);
}


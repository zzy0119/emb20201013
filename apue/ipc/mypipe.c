#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdlib.h>

#define BUFSIZE	32

int main(void)
{
	int pfd[2] = {};
	pid_t pid;
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
		read(pfd[0], buf, BUFSIZE);
		puts(buf);
		close(pfd[0]);
		exit(0);
	}

	sleep(1);
	close(pfd[0]);
	write(pfd[1], "good morning", 12);
	close(pfd[1]);
	wait(NULL);

	exit(0);
ERROR:
	close(pfd[0]);
	close(pfd[1]);
	exit(1);
}


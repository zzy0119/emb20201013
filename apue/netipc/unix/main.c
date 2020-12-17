#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <stdlib.h>

#define BUFSIZE	100

int main(void)
{
	int sv[2];
	pid_t pid;
	char buf[BUFSIZE] = {};

	if (socketpair(AF_UNIX, SOCK_STREAM, 0, sv) == -1) {
		perror("socketpair()");
		exit(1);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		goto ERROR;
	}

	if (pid == 0) {
		close(sv[0]);
		write(sv[1], "hello", 5);
		close(sv[1]);
		exit(0);
	}
	wait(NULL);
	close(sv[1]);
	read(sv[0], buf, BUFSIZE);
	close(sv[0]);
	puts(buf);

	exit(0);
ERROR:
	close(sv[0]);
	close(sv[1]);
	exit(1);
}


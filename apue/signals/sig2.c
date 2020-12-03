#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <signal.h>
#include <unistd.h>

static void handler(int s)
{
	;
}

int main(void)
{
	pid_t pid;

	signal(SIGUSR1, handler);

	pid = fork();
	if (pid < 0) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		pause();
		write(1, "world", 5);
		exit(0);
	}
	write(1, "hello", 5);
	sleep(1);
	kill(0, SIGUSR1);
	wait(NULL);

	exit(0);
}



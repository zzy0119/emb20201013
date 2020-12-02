#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>

int main(void)
{
	pid_t pid, pid2;

	printf("pid:%d, pgid:%d, sid:%d\n", getpid(), \
			getpgrp(), getsid(0));

	pid = fork();
	if (pid < 0) {
		perror("fork()");
		exit(1);
	}
	if (pid == 0) {
		setpgid(0, 0);
		printf("child1 pid:%d, pgid:%d, sid:%d\n", getpid(), \
			getpgrp(), getsid(0));
		sleep(100);
		exit(0);
	}
	pid2 = fork();
	if (pid2 == -1) {
		perror("fork()");
		exit(1);
	}
	// if error
	if (pid2 == 0) {
		if (setpgid(pid2, pid) == -1) {
			perror("setpgid()");
			exit(1);
		}
		printf("child2 pid:%d, pgid:%d, sid:%d\n", getpid(), \
				getpgrp(), getsid(0));
		sleep(100);
		exit(0);
	}
	wait(NULL);
	wait(NULL);

	exit(0);
}


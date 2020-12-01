#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void)
{
	pid_t pid;
	int var = 100;

	printf("pid:%d\n", getpid());
	printf("ppid:%d\n", getppid());

	printf("good morining");
//	pid = fork();
	pid = vfork();
	if (-1 == pid) {
		perror("fork()");
		exit(1);
	}

	if (pid == 0) {
		// child
		var++;
		printf("child var:%d\n", var);
		printf("child pid:%d, child's parent pid:%d\n", getpid(), getppid());
		sleep(1);
		exit(0);
	}
	// wait(NULL);
	printf("var:%d\n", var);
	printf("the calling process pid:%d, parents pid:%d\n", getpid(), getppid());

	exit(0);
}


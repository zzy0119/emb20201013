/*
 现有100～300之间201个数值，筛选哪些是质数，要求201个数值同时计算
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define START 	100
#define END		300

#define PROC_NR	END-START+1	

int is_primer(int n);
int main(void)
{
	pid_t pid;
	
	for (int i = START; i <= END; i++) {
		pid = fork();
		if (pid == -1) {
			perror("fork()");
			exit(1);
		}
		if (pid == 0) {
			if (is_primer(i)) {
				printf("%d is a primer\n", i);
			}
			sleep(3);
			exit(0);
		}
	}

	for (int i = START; i <= END; i++)
		wait(NULL);

	exit(0);
}

int is_primer(int n)
{
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return 0;

	return 1;
}



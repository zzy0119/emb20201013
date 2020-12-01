#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	FILE *fp;
	int ch;

	fp = fopen(argv[1], "r");

	pid_t pid = fork();

	if (pid == 0) {
		ch = fgetc(fp);
		putchar(ch);
		putchar('\n');
		exit(0);
	}
	wait(NULL);
	ch = fgetc(fp);
	putchar(ch);
	putchar('\n');

	exit(0);
}


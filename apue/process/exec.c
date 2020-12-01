#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{

	char *args[] = {"ls", "-l", NULL};
	
	// execl("/bin/ls", "ls", "-l", NULL);
	// execlp("ls", "ls", "-l", NULL);
	execv("/bin/ls", args);

	printf("good bye\n");

	exit(0);
}


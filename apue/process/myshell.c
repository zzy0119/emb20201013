#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <glob.h>

int sep_cmd(char *ptr, glob_t *g);
int main(void)
{
	char *lineptr = NULL;
	size_t n = 0;
	glob_t globstr;
	pid_t pid;

	while (1) {
		printf("[emb@1013]# ");
		if (getline(&lineptr, &n, stdin) == -1) {
			fprintf(stderr, "getline() failed\n");
			exit(1);
		}
		if (!strcmp(lineptr, "exit\n"))
			break;
		// "ls -l"--->seperator
		sep_cmd(lineptr, &globstr);

		pid = fork();
		if (pid < 0) {
			perror("fork()");
			exit(1);
		}
		if (pid == 0) {
			execvp((globstr.gl_pathv)[0], globstr.gl_pathv);
			perror("execvp()");
			exit(1);
		}
		wait(NULL);	
		globfree(&globstr);
	}

	
	exit(0);
}

int sep_cmd(char *ptr, glob_t *g)
{
	char *ret;
	int i = 0;

	while (1) {
		ret = strsep(&ptr, " \n");
		if (NULL == ret)
			break;
		if (!strcmp(ret, ""))
			continue;
		glob(ret, GLOB_NOCHECK | GLOB_APPEND*i, NULL, g);
		i = 1;
	}	

	return 0;
}





#include <stdio.h>
#include <stdlib.h>

long mygetline(char **p, long *n);
int main(void)
{
	char *ptr = NULL;
	size_t n = 0;
	ssize_t nmemb = 0;

	nmemb = mygetline(&ptr, &n);
	if (nmemb == -1) {
		return 1;
	}
	puts(ptr);
	printf("n:%ld\n", n);

	free(ptr);
	ptr = NULL;

	return 0;
}

// 终端读取一行字符串
long mygetline(char **p, long *n)
{
	char ch;
	long i = 0;
	int newline = 0;

	while (1) {
		if (i == *n) {
			// 空间满了
			*n += 10;
			*p = realloc(*p, *n);
			if (*p == NULL)
				return -1;
		}
		if (newline) {
			(*p)[i] = '\0';
			break;
		}
		ch = getchar();
		(*p)[i++] = ch;
		if (ch == '\n') {
			newline = 1;	
		}
	}		

	return i;
}





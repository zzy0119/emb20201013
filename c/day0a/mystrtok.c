#include <stdio.h>
#include <string.h>

static char *start;

char *mystrtok(char *p, const char *delim);
int main(int argc, char *argv[])
{
	char *p = NULL;

	if (argc < 3)	
		return 1;

	while (1) {
		p = mystrtok(argv[1], argv[2]);
		if (NULL == p)
			break;
		puts(p);
		argv[1] = NULL;	
	}

	return 0;
}

char *mystrtok(char *p, const char *delim)
{
	// static char *start = p;	 ???????
	char *ret, *ptr;

	if (p != NULL)
		start = p;

	while (strchr(delim, *start) != NULL) {
		// 第一个元素就是分割符
		start++;
	}
	ptr = start;
	while (*start) {
		ret = strchr(delim, *start);	
		if (ret != NULL) {
			*start = '\0';
			start ++;
			return ptr;
		}
		start ++;
	}

	return NULL;
}



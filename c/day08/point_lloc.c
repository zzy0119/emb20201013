#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *reverstring(const char *s);
int main(void)
{
	char *ret;

	ret = reverstring("hello world");
	puts(ret);

	free(ret);
	ret = NULL;

	return 0;
}

char *reverstring(const char *s)
{
	// char *res = (char *)malloc(strlen(s) + 1);
	char *res = (char *)calloc(strlen(s) + 1, sizeof(char));
	if (NULL == res)
		return NULL;
	for (int i = 0, j = strlen(s)-1; j >= 0;i++, j--) {
		res[i] = s[j];
	}
	
	return res;
}


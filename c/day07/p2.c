#include <stdio.h>

void mystrlen(char *p, int *len);
int main(void)
{
	char *ptr = "good afternoon";
	char str[] = "good afternoon";
	int length;

	mystrlen(ptr, &length);
	printf("%s的长度是%d\n", ptr, length);

	return 0;
}

// 计算给定字符串的长度
void mystrlen(char *p, int *len)
{
	*len = 0;	
	while (*p++)
		(*len)++;
}


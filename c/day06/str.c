#include <stdio.h>

int mystrcpy(char dest[], char src[]);
int mystrcat(char dest[], char src[]);
int main(void)
{
	char str[] = "hello world";
	char str2[11] = {'h', 'e', 'l', 'l', 'o', \
	' ', 'w', 'o', 'r', 'l', 'd'}; // 不是字符串，普通数组
	int i;
	char str3[50] = "hhhhhhhhhhhhhhhhh";

	printf("%ld\n", sizeof(str));

	// 字符串长度
	for (i = 0; str[i]; i++)
		;
	printf("长度:%d\n", i);

	mystrcpy(str3, str);
	printf("%s\n", str3);

	mystrcat(str3, str);
	printf("%s\n", str3);

	return 0;
}

// 字符串copy
int mystrcpy(char dest[], char src[])
{
	int i;

	for (i = 0; src[i] != '\0'; i++) {
		dest[i] = src[i];
	}
	dest[i] = '\0';

	return 0;
}

// 字符串拼接cat
int mystrcat(char dest[], char src[])
{
	int i;

	for (i = 0; dest[i]; i++)
		;
	mystrcpy(dest+i, src);

	return 0;
}





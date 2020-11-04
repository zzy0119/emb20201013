#include <stdio.h>

int main(void)
{
	char str[] = "hello world";
	const char *s = str; // 通过指针s,不能修改*s中的内容----->常量(的)指针
	char *const p = str;// p只读的--->指针(的)常量
	char const *q = str; //等同于const char *

	// s[2] = 'e'; 错误的
	s++;

	p[2] = 'e';
	p++;

	return 0;
}


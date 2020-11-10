#include <stdio.h>

void swap2num(int *n1, int *n2);
int main(void)
{
	int num1, num2;
	// 定义
	int *p; // 野指针

	p = &num1;

	num1 = 100;
	num2 = 800;
	swap2num(&num1, &num2);
	printf("num1:%d, num2:%d\n", num1, num2);

	return 0;
}

void swap2num(int *n1, int *n2)
{
	int t;
	t = *n1;
	*n1 = *n2;
	*n2 = t;
}



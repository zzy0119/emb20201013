#include <stdio.h>

int main(void)
{
	int var;

	printf("请输入一个整型变量:");
	scanf("%d", &var);

	if (var % 2 == 0) {
		printf("这就是我想要的\n");
		printf("var:%d\n", var);
	} else
		printf("我需要一个偶数\n");

	return 0;
}

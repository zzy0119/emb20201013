#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

static jmp_buf env;

static int div2num(int m, int n)
{
	if (n == 0) {
		longjmp(env, 100);	
	}

	return m / n;
}


int main(void)
{
	int num1, num2;
	int ret;

	// 设置跳转点
	ret = setjmp(env);
	if (ret == 0) {
		// 非跳转
		printf("输入两个整型变量:");
	} else {
		printf("请重新输入:");
	}
	scanf("%d%d", &num1, &num2);
	printf("%d\n", div2num(num1, num2));

	exit(0);
}


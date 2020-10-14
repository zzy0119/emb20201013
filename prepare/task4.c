#include <stdio.h>

int main(void)
{
	int n;
	int res = 0;

	printf("输入一个整型数:");
	scanf("%d", &n);

	for (int i = 1; i <= n; i++) {
		// res = res + n;
		res += i;
	}

	printf("结果:%d\n", res);

	return 0;
}


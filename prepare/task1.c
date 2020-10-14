/*
 1. 读入两个整型数，比较其大小
 2. 读入一个三位整型数,判断其是否为对称整型数.
 111 121 123
 */
#include <stdio.h>

int main(void)
{
	int m, n;

	// 读入
	printf("请输入两个整型数:");
	scanf("%d%d", &m, &n);

	if (m > n) {
		printf("%d 大于 %d\n", m, n);
	} else {
		printf("%d 小于 %d\n", m, n);
	}

	return 0;
}


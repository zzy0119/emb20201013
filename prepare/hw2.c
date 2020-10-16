#include <stdio.h>

int main(void)
{
	int n, tmp;
	int rever_n = 0;

	printf("请输入一个整型数:");
	scanf("%d", &n);

	// 逆序数
	tmp = n;

	while (tmp > 0) {
		rever_n = tmp % 10 + rever_n * 10;	
		tmp = tmp / 10; // tmp /= 10
	}

	if (rever_n == n) {
		printf("是回文\n");
	} else {
		printf("不是回文\n");
	}

	return 0;
}


#include <stdio.h>

int main(void)
{
	int n;

	printf("请输入一个三位整型:");
	scanf("%d", &n);

	if (n < 100 || n >= 1000) {
		printf("不符合要求\n");
	} else {
		if (n / 100 == n % 10) {
			printf("%d 是一个对称数\n", n);
		} else {
			printf("%d 不是对称数\n", n);
		}
	}

	return 0;
}


#include <stdio.h>

int main(void)
{
	int n;

	printf("请输入一个整型数:");
	scanf("%d", &n);

	while (n > 0) {
		printf("%d ", n % 10);
		n = n / 10;
	}

	return 0;
}


#include <stdio.h>

int main(void)
{
	int n;
	int flag = 0;

	printf("输入一个变量:");
	scanf("%d", &n);

	if (n <= 1)	{
		printf("不是质数\n");
		return 1;
	}

	for (int i = 2; i < n; i++) {
		if (n % i == 0) {
			flag = 1;
			break;
		}
	}
	if (!flag) {
		printf("%d 是一个质数\n", n);
	} else {
		printf("%d不是一个质数\n", n);
	}

	return 0;
}


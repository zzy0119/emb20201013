#include <stdio.h>

int main(void)
{
	int i;

	for (i = 0; i < 10; i++) {
		if (i % 2)
			continue;// 结束本次循环，继续下一次
		if (i > 5)
			break; // 跳出最近循环
		printf("* ");
	}
	printf("\n");

	return 0;
}



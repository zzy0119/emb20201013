#include <stdio.h>

int main(void)
{
	int n;
	
	printf("请输入变量n：");
	scanf("%d", &n);

	n = n | 0x1 << 3;
	printf("n:%d\n", n);
	n = n & ~(0x1 << 5);
	printf("n:%d\n", n);

	return 0;
}


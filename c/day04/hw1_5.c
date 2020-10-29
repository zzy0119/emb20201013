#include <stdio.h>

int reverse_n(int n);
int main(void)
{
	int num;

	printf("请输入一个整型变量:");
	scanf("%d", &num);

	printf("%d的逆序数为%d\n", num, reverse_n(num));	

	return 0;
}

int reverse_n(int n)
{
	int flag = 1;
	int res = 0;

	if (n < 0) {
		n = -n;
		flag = -1;
	}

	while (n) {
		res = res * 10 + n % 10;	
		n /= 10;	
	}
	return res * flag;
}


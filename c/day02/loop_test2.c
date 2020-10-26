#include <stdio.h>

int main(void)
{
	int n, low;	

	printf("输入n:");
	scanf("%d", &n);

	for (; n > 0 ; n /= 10) {
		low = n % 10;	
		printf("%d ", low);
	}
	printf("\n");

	return 0;
}


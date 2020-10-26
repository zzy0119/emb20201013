#include <stdio.h>

int main(void)
{
	int n = 100;
	int sum = 0;

	for (n = 1; n <= 100; n++ ) {
		sum = 0;
		for (int i = 1; i <= n; i++) {
			sum += i;
		}
		printf("%d的前n项和为%d\n", n, sum);
	}

	return 0;
}


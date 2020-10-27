#include <stdio.h>

int main(void)
{
	for (int i = 1; i <= 9; i++) {
		for (int j = 1; j <= i; j++) {
			printf("\33[32m\33[45m%d*%d=%-3d", j, i, j*i);
			printf("\33[0m");
		}
		printf("\n");
	}

	return 0;
}


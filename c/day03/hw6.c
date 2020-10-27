#include <stdio.h>

int main(void)
{
	int pre1, pre2, cur;

	pre1 = pre2 = 1;

	printf("1, 1, ");
	for (int i = 0; i < 8; i++) {
		cur  = pre1 + pre2;
		printf("%d, ", cur);
		pre2 = pre1;
		pre1 = cur;
	}
	printf("\b\b \n");

	return 0;
}


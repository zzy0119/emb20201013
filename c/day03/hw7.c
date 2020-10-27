#include <stdio.h>

int main(void)
{
	int row, i, j;

	for (row = 0; row < 10; row ++) {
		// 空格	
		for (i = 0; i < 10-row-1; i++) {
			printf(" ");
		}
		for (j = 0; j < 2*row+1; j++) {
			printf("*");
		}
		printf("\n");
	}

	for (row = 0; row < 10; row++) {
		// 空格
		for (i = 0; i < row; i++) 
			printf(" ");
		for (j = 0; j < 4; j++)
			printf("*");
		printf("\n");
	}

	for (row = 0; row < 30; row ++) {
		for (i = 0; i <= row; i++) {
			printf("%c", 'A'+i%26);
		}
		printf("\n");
	}

	return 0;
}


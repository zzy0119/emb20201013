#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main(void)
{
	int arr2[3][2];
	int arr[3][4] = {
		{1,2,3,4},
		{11,22,33,44},
		{111,222,333,44}
	}; // 初始化
	int i, j;

	srand(getpid());

	// 赋值
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			arr2[i][j] = rand() % 100;
		}
	}

	// 遍历
	for (i = 0; i < 3; i++) {
		for (j = 0; j < 2; j++) {
			printf("%d ", *(*(arr2+i)+j));
		}
		printf("\n");
	}

	return 0;
}


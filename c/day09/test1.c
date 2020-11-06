#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#define N	10

/*
 定义一个又10个整型数组成的数组，元素值随机产生100以内，
 定义一个接口函数，将给定数组的最大值最小值平均值返回
 */
void test_arr(int *arr, int n, int *max, int *min, int *avg);
int main(void)
{
	int array[N] = {};
	int i;
	int maxnum, minnum, argnum;
			
	srand(getpid());
	for (i = 0; i < N; i++) {
		array[i] = rand() % 100;	
		printf("%d ", array[i]);
	}
	printf("\n");

	test_arr(array, sizeof(array) / sizeof(array[0]), &maxnum, \
			&minnum, &argnum);
	printf("最大值:%d, 最小值:%d, 平均值:%d\n", \
			maxnum, minnum, argnum);

	return 0;
}

void test_arr(int *arr, int n, int *max, int *min, int *avg)
{
	int sum = arr[0];
	*max = *min = arr[0];

	for (int i = 1; i < n; i++) {
		sum += arr[i];
		if (arr[i] > *max)
			*max = arr[i];
		if (arr[i] < *min)
			*min = arr[i];
	}
	*avg = sum / n;
}



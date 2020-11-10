#include <stdio.h>

int main(void)
{
	int arr[] = {5,1,9,4,6,8,2,1,1,3};
	int n, tmp;
	int max_index;

	n = sizeof(arr) / sizeof(int);
	// 选择排序
	for (int i = 0; i < n-1; i++) {
		max_index = i;
		for (int j = i+1; j < n; j++) {
			if (arr[j] > arr[max_index])
				max_index = j;
		}
		// max_index-->最大
		if (i != max_index) {
			tmp = arr[i];
			arr[i] = arr[max_index];
			arr[max_index] = tmp;
		}
	}


	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}


#include <stdio.h>

int main(void)
{
	int arr[] = {5,1,9,4,6,8,2,1,1,3};
	int n, tmp;

	n = sizeof(arr) / sizeof(int);
	// 选择排序
	for (int i = 0; i < n-1; i++) {
		for (int j = i+1; j < n; j++) {
			if (arr[i] < arr[j]) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}


	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}


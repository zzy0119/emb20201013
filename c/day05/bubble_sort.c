#include <stdio.h>

int main(void)
{
	int arr[] = {5,1,9,4,6,8,2,1,1,3};
	int n, tmp;

	n = sizeof(arr) / sizeof(int);
	for (int i = 0; i < n-1; i++) {
		for (int j = 0; j < n-i-1; j++) {
			if (arr[j] > arr[j+1]) {
				tmp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = tmp;	
			}
		}
	}

	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}


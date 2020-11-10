#include <stdio.h>

int main(void)
{
	int arr[] = {5,1,9,4,6,8,2,1,1,3};
	int n, tmp;
	int i, j;

	n = sizeof(arr) / sizeof(int);
	// 直接插入排序
	for ( i = 1; i < n; i++) {
		tmp = arr[i];
		for (j = i-1; j >= 0; j --) {
			if (tmp <= arr[j])
				break;
			arr[j+1] = arr[j];
		}
		arr[j+1] = tmp;	
	}


	for (int i = 0; i < n; i++)
		printf("%d ", arr[i]);
	printf("\n");

	return 0;
}


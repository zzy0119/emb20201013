#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define N	20

void sort_arr(int a[], int n);
int find_num(int a[], int n, int fn);
int main(void)
{
	int arr[N];
	int i;
	int num, ret;

	// 随机数提供种子
//	srand(time(NULL));
	srand(getpid());

	// 随机产生
	for (i = 0; i < N; i++) {
		arr[i] = rand() % 100;
		printf("%d ", arr[i]);
	}
	printf("\n");

	sort_arr(arr, N); // 排序
	for (i = 0; i < N; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	printf("你要找哪个元素:");
	scanf("%d", &num);
	if ((ret = find_num(arr, N, num)) < 0) {
		printf("没有你要查找的元素\n");
	} else {
		printf("找到了，在%d位置\n", ret);
	}

	return 0;
}

// 为数组排序
void sort_arr(int a[], int n)
{
	int i, j;	

	for (i = 0; i < n-1; i++) {
		for (j = 0; j < n-i-1; j++) {
			if (a[j] > a[j+1]) {
				a[j] = a[j] ^ a[j+1];
				a[j+1] = a[j] ^ a[j+1];
				a[j] = a[j] ^ a[j+1];
			}
		}
	}
}

// 二分查找
int find_num(int a[], int n, int fn)
{
	int low, high, mid;

	low = 0;
	high = n-1;
	while (low <= high) {
		mid = (low+high) / 2;
		if (fn == a[mid])
			return mid;
		else if (fn > a[mid])
			low = mid+1;
		else 
			high = mid-1;
	}

	return -1;
}







#include <stdio.h>

void * maxArr(void *arr, int n, int size, int(*cmp)(void *, void *));

static int cmpInt(void *d1, void *d2)
{
	int *da1 = d1;
	int *da2 = d2;

	return *da1 - *da2;
}

static int cmpChar(void *d1, void *d2)
{
	char *da1 = d1;
	char *da2 = d2;

	return *da1 - *da2;
}

int main(void)
{
	int a[] = {3,2,1,6,7,9,4,15,1};
	char str[] = "hello world";

	int *max = maxArr(a, sizeof(a)/sizeof(*a), sizeof(int), cmpInt);
	printf("最大值:%d\n", *max);

	char *p = maxArr(str, sizeof(str) / sizeof(*str), \
			sizeof(char), cmpChar);
	printf("最大的元素是:%c\n", *p);

	return 0;
}

/*
 求得数组的所有成员的最大值
 */
void * maxArr(void *arr, int n, int size, int(*cmp)(void *, void *)) 
{
	void *pmax = arr; // 假定第一个元素就是最大的

	for (int i = 1; i < n; i++) {
		if (cmp(pmax, (char *)arr+i*size) < 0) {
			pmax = (char *)arr+i*size;
		}
	}

	return pmax;
}



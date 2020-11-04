#include <stdio.h>

int main(void)
{
	int arr[8] = {1, 4, 6, 3, 35, 8, 10, 7};
	int *p;

	p = arr;
	printf("%d\n", *p++); // 1
	printf("%d\n", (*p)++); // 4
	printf("%d\n", *(p++)); // 5
	printf("%d\n", ++*p); // 7
	printf("%d\n", *++p); // 3

	for (int i = 0; i < 8; i++)
		printf("%d ", arr[i]);
	printf("\n"); 

	return 0;
}


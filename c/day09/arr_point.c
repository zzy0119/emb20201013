#include <stdio.h>

int main(void)
{
	int arr[2][3] = {1,2,3,4,5,6};
	int (*p)[3]= arr; // 数组指针

	/*
	 p+1
	 *(p+1)
	 *(p+1) + 2
	 *(*(p+1) + 2)
	 *p+2
	 *(*p+2)
	 */

	return 0;
}


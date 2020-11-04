#include <stdio.h>

int main(void)
{
	void *p; // 万能指针--》存储任意类型地址 不能参与运算
	int arr[10] = {1,2,3,4,5,6,7,8,9,10};
	p = arr;
	int *a1 = arr;
	int *a2 = arr+3;

	// p+1;错

	printf("%ld\n", a2-a1);

	return 0;
}


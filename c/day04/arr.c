#include <stdio.h>

int main(void)
{
	// 数组定义
	int arr[5]; // 随机值
	int arr2[3] = {}; // 0
	int arr3[3] = {1}; // 第一个为1 其他为0
	int arr4[13] = {1,2,3, [9]=5};

	// 元素赋值
	for (int i = 0; i < 5; i++) {
		arr[i] = i+1; // i数组下标，从0开始,到n-1
	}

	// 遍历
	for (int i = 0; i < 5; i ++)
		// printf("%d ", arr[i]);
		printf("%d ", i[arr]);
	printf("\n");

	return 0;
}


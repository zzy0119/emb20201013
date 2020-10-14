#include <stdio.h>

int main(void)
{
	// 判断一个数的奇偶性

	// 哪个数--->读入用户待判断的数值
	int var;

	scanf("%d", &var);
		
	// 是否能被2整除
	if (var % 2 == 0) {
		// 输出
		printf("%d 是一个偶数\n", var);
	} else {
		printf("%d 是一个奇数\n", var);
	}

	return 0;
}


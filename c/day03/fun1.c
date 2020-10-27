#include <stdio.h>

// 声明
int is_leapyear(int);

int main(void)
{
	int year;
	int ret;

	printf("请输入年份:");
	scanf("%d", &year);

	// 使用接口---》函数的调用
	ret = is_leapyear(year); // y = year
	if (ret)
		printf("%d年闰年\n", year);
	else 
		printf("%d年平年\n", year);

	return 0;
}

/*
 函数的定义:判断给定的年份是否为闰年
 0 不是
 1 是
 */
int is_leapyear(int y)
{
	return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
}








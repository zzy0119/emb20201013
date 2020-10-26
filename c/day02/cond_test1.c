/*
 1.读入一个两位数(10~100),要求求出这个输入逆序数
 2.读入一个年份，判断是否为闰年 
 */
#include <stdio.h>

int main(void)
{
	int var;
	int res;

	printf("请输入一个两位数:");
	scanf("%d", &var);

	if (var >= 10 && var < 100) {
		// 求逆序数
		res = var % 10;
		res = res * 10 + var / 10;
		printf("逆序数:%d\n", res);
	} else {
		printf("你输入不符合要求\n");
	}

	return 0;
}

	







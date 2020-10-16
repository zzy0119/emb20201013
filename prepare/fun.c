#include <stdio.h>

// 声明
int is_leap(int y);
int month_days(int m, int y);
int main(void)
{
	int year, month;
	int sumdays = 0;
	int firstweek;

	// 读入 do .... while()
	while (1) {
		printf("输入90年后日期(y/m):");
		scanf("%d/%d", &year, &month);
		if (year >= 1990 && month >= 1 && month <= 12)
			break;// 跳出循环
	}
	// 统计总天数
	// 1990~year
	for (int y = 1990; y < year; y++) {
		// 调用
		sumdays += (365+is_leap(y));
	}
	// year.1.1~year.month.1
	for (int m = 1; m < month; m++) {
		sumdays += month_days(m, year);
	}
	sumdays ++;

	// %7
	firstweek = sumdays % 7;
	printf("星期%d\n", firstweek);

	return 0;
}

// 函数: 定义:实现 声明 调用
/*
is_leap:判断给定的年份是否为润年
y:待判断的年份
return:0 no  1 yes
 */
int is_leap(int y)
{
	if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0)
		return 1;
	return 0;
}

/*
 函数功能:计算出给定的月份有多少天
 */
int month_days(int m, int y)
{
	int sumdays = 0;

	if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8\
			|| m == 10 || m == 12) {
		sumdays = 31;
	} else if (m == 4 || m == 6 || m == 9 || m == 11) {
		sumdays = 30;
	} else {
		sumdays = 28+is_leap(y);
	}

	return sumdays;
}






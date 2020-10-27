#include <stdio.h>

int is_leapyear(int y);
int days_month(int m, int y);
int days_year(int y);
int main(void)
{
	int y, m; // 接口函数的y, m不是同一个变量
	int i;
	int sum = 0;
	int firstweek;
	int monthdays;

	printf("输入年份:");
	scanf("%d", &y);
	printf("输入月份:");
	scanf("%d", &m);

	// 1800,1,1--->3
	// [1800,y-1]
	for (i = 1800; i < y; i++) {
		sum += days_year(i);
	}
	// [y.1, y.m)
	for (i = 1; i < m; i++) {
		sum += days_month(i, y);
	}
	sum += 1;// y.m.1

	firstweek = (sum+2) % 7;
	// printf("星期%d\n", firstweek);

	monthdays = days_month(m, y);
	// 打印日历
	printf("      %d月%d\n", m, y);
	printf("日 一 二 三 四 五 六\n");
	for (i = 0; i < firstweek; i++)	
		printf("   ");
	for (i = 1; i <= monthdays; i++) {
		printf("%2d%c", i, (i+firstweek) % 7 == 0 ? '\n':' ');
	}
	printf("\n");

	return 0;
}

// 判断是否为闰年
int is_leapyear(int y)
{
	return y % 4 == 0 && y % 100 != 0 || y % 400 == 0;
}

// 计算给定的月份有多少天
int days_month(int m, int y)
{
	int ret;

	switch (m){
		case 1: 
		case 3:
		case 5:
		case 7:
		case 8:
		case 10:
		case 12:
			ret = 31;
			break;
		case 4:
		case 6:
		case 9:
		case 11:
			ret = 30;
			break;
		case 2:
			ret = is_leapyear(y) ? 29:28;
			break;
		default:
			ret = -1;
			break;
	}

	return ret;
}

// 计算给定的年份有多少天
int days_year(int y)
{
	return 365 + is_leapyear(y);
}



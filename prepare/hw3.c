#include <stdio.h>

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
		if (y % 4 == 0 && y % 100 != 0 || y % 400 == 0) {
			sumdays += 366;
		} else {
			sumdays += 365;
		}
	}
	// year.1.1~year.month.1
	for (int m = 1; m < month; m++) {
		if (m == 1 || m == 3 || m == 5 || m == 7 || m == 8\
				|| m == 10 || m == 12) {
			sumdays += 31;
		} else if (m == 4 || m == 6 || m == 9 || m == 11) {
			sumdays += 30;
		} else {
			if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0	) {
				sumdays += 29;
			} else {
				sumdays += 28;
			}
		}
	}
	sumdays ++;

	// %7
	firstweek = sumdays % 7;
	printf("星期%d\n", firstweek);

	return 0;
}


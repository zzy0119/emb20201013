/*
 利用所学知识，输入一个日期(y/m/d),计算这是这一年中的
 第几天(2020/10/26)
 */
#include <stdio.h>

int main(void)
{
	int y, m, d;
	int days = 0;

	printf("输入日期(y/m/d):");
	scanf("%d/%d/%d", &y, &m, &d);

	switch (m-1) {
		case 11:
			days += 30;
		case 10:
			days += 31;
		case 9:
			days += 30;
		case 8:
			days += 31;
		case 7:
			days += 31;
		case 6:
			days += 30;
		case 5:
			days += 31;
		case 4:
			days += 30;
		case 3:
			days += 31;
		case 2:
			days += (y % 4 == 0 && y % 100 != 0 || \
				   y % 400 == 0 ? 29 : 28);
		case 1:
			days += 31;
			break;
		default:
			break;
	}
	days += d;
	printf("%d/%d/%d是这一年的第%d天\n", y, m, d, days);

	return 0;
}



/*
	读入用户输入的日期(y/m/d) ("%d/%d/%d"),计算这是这一年的第几天
	2020/10/14 
	2020/1/1~2020/10/1 + 14
 */
#include <stdio.h>

int main(void)
{
	int y, m, d;
	int sum = 0;

	printf("y/m/d:");
	scanf("%d/%d/%d", &y, &m, &d);

	// 总天数
	for (int i = 1; i < m; i ++) {
		if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 \
				|| i == 10 || i == 12) {
			sum += 31;
		} else if (i == 4 || i == 6 || i == 9 || i == 11) {
			sum += 30;
		} else {
			// 2
			sum += (28 + (y % 4 == 0 && y % 100 != 0 || y % 400 == 0));
		}
	}
	sum += d;

	printf("%d/%d/%d是%d中的第%d天\n", y, m, d, y, sum);

	return 0;
}



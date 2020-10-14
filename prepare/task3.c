#include <stdio.h>

int main(void)
{
	int month, year;

	printf("输入月份:");
	scanf("%d", &month);

	if (month == 1 || month == 3 || month == 5 || \
			month == 7 || month == 8 || month == 10 || \
			month == 12)
		printf("%d有31天\n", month);
	else if (month == 4 || month == 6 || month == 9 || month == 11) {
		printf("%d有30天\n", month);
	} else if (month == 2){
		printf("哪一年:");
		scanf("%d", &year);
		if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) // man operator
			printf("%d月有29天\n", month);
		else
			printf("%d月有28天\n", month);
	} else {
		printf("不知道\n");
	}

	return 0;
}


/*
 判断成绩分数段:
A: 90~100
B: 80~89
C: 70~79
D: 60~69
E: 0~60
 */ 
#include <stdio.h>

int main(void)
{
	int score, n;

	printf("请输入成绩:");
	scanf("%d", &score);

	if (!(score >= 0 && score <= 100)) {
		printf("成绩无效\n");	
		return 1;
	}

	n = score / 10;

	// 取得十位
	if ( n == 9 || n == 10)
		printf("A\n");
	else if (n == 8)
		printf("B\n");
	else if (n == 7) 
		printf("C\n");
	else if (n == 6)
		printf("D\n");
	else 
		printf("E\n");

	return 0;
}








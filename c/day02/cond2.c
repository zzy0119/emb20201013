/*
 读入用户输入的一个成绩,判断是优还是良还是及格
 90~100优
 70~89 良
 60~79 及格
 0~59 不及格
 */
#include <stdio.h>

int main(void)
{
	int score;
	
	printf("成绩：");
	scanf("%d", &score);

	if (score >= 90 && score <= 100)
		printf("优秀\n");
	else if (score >= 70 && score < 90)
		printf("良好\n");
	else if (score >= 60 && score < 70)
		printf("及格\n");
	else if (score >= 0 && score < 60) 
		printf("不及格\n");
	else
		printf("输入无效\n");
	
	return 0;
}


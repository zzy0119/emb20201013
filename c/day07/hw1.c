#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

#define NUM	20
#define N	11

int main(void)
{
	int score[NUM];	
	int grade[N] = {};
	int i, j;

	srand(getpid());

	// 读入
	for (i = 0; i < NUM; i++) {
		printf("请输入第%d个学生的成绩:", i+1);
		// scanf("%d", score+i);
		score[i] = rand() % 101;
		grade[score[i] / 10]++;
		printf("%d\n", score[i]);
	}
	printf("\n");

	// 输出
	printf("100:");
	for (i = 0; i < grade[10]; i++)
		printf("* ");
	printf("\n");
	for (i = 9; i >= 0; i--) {
		printf("%2d~%2d:", i*10, i*10+9);
		for (j = 0; j < grade[i]; j++)
			printf("* ");
		printf("\n");
	}

	return 0;
}


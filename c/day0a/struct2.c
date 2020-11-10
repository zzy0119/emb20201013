#include <stdio.h>
#include <string.h>

// 定义学生结构(姓名，成绩，年龄),读入10个学生信息，求所有所生的
// 最高成绩和最低成绩，并打印其信息

#define N	10

typedef struct {
	int score;
	char name[32];
	int age;
}stu;

int main(void)
{
	stu s[N];
	int max_index, min_index;

	max_index = min_index = 0;
	for (int i = 0; i < N; i++) {
		printf("请输入第%d学生的姓名:", i+1);
		scanf("%s", s[i].name);
		printf("请输入第%d学生的成绩:", i+1);
		scanf("%d", &s[i].score);
		printf("请输入第%d学生的年龄:", i+1);
		scanf("%d", &s[i].age);

		if (s[i].score > s[max_index].score)
			max_index = i;
		if (s[i].score < s[min_index].score)
			min_index = i;
	}
	printf("最高成绩:%s %d %d\n", s[max_index].name,\
		   	s[max_index].age, s[max_index].score);
	printf("最低成绩:%s %d %d\n", s[min_index].name,\
		   	s[min_index].age, s[min_index].score);

	return 0;
}


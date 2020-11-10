#include <stdio.h>

// 复合类型--->结构体
struct student_st {
	char *name;
	int age;
	float score;
}g_s1, *g_p1;

int main(void)
{
	struct student_st s = {"c", 50, 100};
	struct student_st s2;
	struct student_st *p;
	struct student_st arr[3];

	s2 = s;
	p = &s;
	printf("%s, %d, %f\n", s2.name, s2.age, s2.score);
	printf("%s, %d, %f\n", p->name, p->age, p->score);

	return 0;
}


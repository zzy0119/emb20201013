#include <stdio.h>

typedef void (*p)(int);

typedef int *TYPEA;
#define TYPEB	int *

void test(int n);
int main(void)
{
	TYPEA p1, p2;
	TYPEB q1, q2; // int *q1, q2
	p a = test;

	a(100);

	return 0;
}

void test(int n)
{
	printf("n:%d\n", n);
}



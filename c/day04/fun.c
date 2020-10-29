#include <stdio.h>

void test(int m, int n, int p);
int main(void)
{
	volatile int var = 10;

	test(var++, var++, var++); // p = var++;

	// var --> 13
	printf("%d %d %d\n", var++, --var, var++);

	return 0;
}

void test(int m, int n, int p)
{
	printf("m:%d, n:%d, p:%d\n", m, n, p);
}


#include <stdio.h>

extern int glob;

int add(int m, int n);
int main(void)
{
	printf("%d\n", add(10, 20));
	printf("glob:%d\n", glob);

	return 0;
}


#include <stdio.h>

// 递归

int sum_n(int n);
int fib(int n);
int main(void)
{
	for (int i = 1; i <= 20; i++)
		printf("%d ", fib(i));

	return 0;
}

int sum_n(int n)
{
	// n--->n + sum_n(n-1)
	if (n == 0)
		return 0;
	return n + sum_n(n-1);
}

int fib(int n)
{
	if (n == 1 || n == 2)
		return 1;
	if (n < 1)
		return -1;
	return fib(n-1) + fib(n-2);
}









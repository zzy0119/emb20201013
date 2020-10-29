#include <stdio.h>

int add_evens(int n);
int main(void)
{
	int var;	

	scanf("%d", &var);
	printf("%d\n", add_evens(var));

	return 0;
}

static int is_even(int n)
{
	return !(n % 2);
}

int add_evens(int n)
{
	int sum = 0;
	int tmp;

	while (n) {
		tmp = n % 10;
		if (is_even(tmp)) {
			sum += tmp;	
		}
		n /= 10;
	}
	return sum;
}


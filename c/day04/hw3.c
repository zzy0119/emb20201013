#include <stdio.h>

int maxCommonDivisor(int m, int n);
int minCommonMultiple(int m, int n);

int main(void)
{
	int var1, var2;

	scanf("%d%d", &var1, &var2);

	printf("%d和%d的最大公约数是:%d\n", var1, var2, maxCommonDivisor(var1, var2));
	printf("%d和%d的最小公倍数是:%d\n", var1, var2, minCommonMultiple(var1, var2));
	
	return 0;
}

// 求两个数的最大公约数
int maxCommonDivisor(int m, int n)
{
	int t;	
	if (m < n) {
		t = m;
		m = n;
		n = t;
	}

	for (t = n; t > 0; t--) {
		if (m % t == 0 && n % t == 0)
			break;
	}
	return t;
}
int minCommonMultiple(int m, int n)
{
	return m * n / maxCommonDivisor(m, n);
}






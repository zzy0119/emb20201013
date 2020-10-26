/*
1. 读入一个整型数，求得其前n项和 
2. 读入一个整型,求得其每一位
3. 判断1~100之间有多个同时能被3和5整除的数 
 */
#include <stdio.h>

int main(void)
{
	int n;
	int res = 0, i;

	printf("请输入一个整型:");
	scanf("%d", &n);

	for (i = 1; i <= n; i++) {
		res += i;
	}
	printf("%d的前n项和为%d\n", n, res);

	return 0;
}


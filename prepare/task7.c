/*
 定义一下接口函数
 	1.判断一个整型数是否是质数
	2.求得两个整型数中较大的那个一数值
	3.水仙花数是一个三位数(每一位的立方和是这个数值本身)，
	写一个函数，判断给定的数值是否是水仙花数
	153==1*1*1+5*5*5+3*3*3
 */
#include <stdio.h>

int is_primer(int n);
int max2num(int a, int b);
int is_flower(int n);
int main(void)
{
#if 0
	int num;

	printf("请输入一个整型数：");
	scanf("%d", &num);

	if (is_primer(num))
		printf("%d是一个质数\n", num);
	else
		printf("%d不是一个质数\n", num);
#endif
#if 0
	int num1, num2;
	int max;

	printf("输入两个整型数:");
	scanf("%d%d", &num1, &num2);

	max = max2num(num1, num2);
	printf("较大的是:%d\n", max);
#endif

	for (int i = 100; i < 1000; i ++) {
		if (is_flower(i)) {
			printf("%d是一个水仙花数\n", i);
		}
	}

	return 0;
}

/*
n:待计算的数值
return:1 是 0 不是
 */
int is_primer(int n)
{
	if (n == 2)
		return 1;
	if (n < 2)
		return 0;
	for (int i = 2; i < n; i++) {
		if (n % i == 0)
			return 0;
	}

	return 1;
}

int max2num(int a, int b)
{
	if (a > b)
		return a;
	return b;
}

// 判断是否是水仙花数
int is_flower(int n)
{
	int sum = 0;
	int tmp, save;

	if (n < 100 || n >= 1000)
		return 0;

	save = n;
	while (n > 0) {
		tmp = n % 10;	
		sum += tmp*tmp*tmp;
		n /= 10;
	}
	return save == sum;
}








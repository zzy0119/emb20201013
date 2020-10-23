#include <stdio.h>

int main(void)
{
	// 存储--->空间--->定义变量
	// 变量名--->标识符(函数名，类型名):由字母，数字，下划线组成，数字不开头，避开c关键字,区分大小写
	// 类型:数值类型 字符类型 复合类型 指针类型
	// 数值类型：整型和实型
	// 整型:short int long (long long)
	// 实型:float double long double
	// 字符类型:char
	// 空类型:void 
	// 有符号:signed 无符号:unsigned
	printf("short:%ld\n", sizeof(short));
	printf("int:%ld\n", sizeof(int));
	printf("long:%ld\n", sizeof(long));
	printf("long long:%ld\n", sizeof(long long));
	printf("float:%ld\n", sizeof(float));
	printf("double:%ld\n", sizeof(double));
	printf("long double:%ld\n", sizeof(long double));
	printf("char:%ld\n", sizeof(char));

	// 定义
	int var1;
	// 初始化
	char c = 'p';	

	// 赋值
	var1 = 100;

	printf("var = %d, c = %c\n", var1, c);

	return 0;
}


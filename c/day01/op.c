#include <stdio.h>

int main(void)
{
	// 算术运算符 * / % + -
	int var = 10;
	int res;

	res = var % 2;
	printf("res:%d\n", res);
	// 位运算符
	res = var << 1;
	printf("res:%d\n", res);
	res = var >> 1;
	printf("res:%d\n", res);
	var = 0x1;
	res = ~var;
	printf("%d\n", res);
	var = 10;
	res = var & 4; // 只有同时为1,结果为1
	printf("%d\n", res);
	res = var | 4; // 只要有一个为1，结果就为1
	printf("%d\n", res);
	// 如果将变量a的第三位置1,又如何将a的第三位清零
	var = 18;// 10010--->11010
	var = var | (0x1 << 3);
	printf("var:%d\n", var);
	var = var & ~(0x1 << 3);
	printf("var:%d\n", var);
	var = 10;
	res = var ^ 15; // 相同为0,不同为1
	printf("res:%d\n", res);
	// 交换
	printf("交换前var:%d, res:%d\n", var, res);
	var = var ^ res;
	res = var ^ res;
	var = var ^ res;
	printf("交换后var:%d, res:%d\n", var, res);
	// 逻辑运算符
	var = -10 && 0;
	printf("var:%d\n", var);
	var = -10 || 0;
	printf("var:%d\n", var);
	// 自增自减运算符 ++ --	
	var = 10;
	res = var ++; // var = var + 1
	printf("res:%d, var:%d\n", res, var);
	var = 10;
	res = ++var; // var = var + 1
	printf("res:%d, var:%d\n", res, var);

	var = 0;
	res = 1 && var++;
	printf("res:%d, var:%d\n", res, var);

	res = var || var ++;
	printf("res:%d, var:%d\n", res, var);
	
	// 条件运算符
	res = !var ? 100 : -10;
	printf("res:%d\n", res);

	res = 2020 % 4 == 0 && 2020 % 100 != 0 || 2020 % 400 == 0 ? 29 : 28;
	printf("%d\n", res);

	// 关系运算符
	var = 10;
	res = var % 2 != 0 && var > 5 ? printf("大于5的奇数\n"):printf("不符合条件\n");
	printf("res:%d\n", res);

	// 赋值运算符
	var += 10; // var = var + 10
	printf("var:%d\n", var);
	var %= 2;// var = var % 2;
	printf("var:%d\n", var);

	// 逗号运算符
	res = (var, var + 10, var ++);
	printf("var:%d, res:%d\n", var, res);

	// 
	printf("%d\n", *&var);
	// a[b]--->*(a+b)	
	char ch = 'a';
	// var = (int)ch;// 强制转换
	var = ch;// 隐式转换
	printf("var:%d\n", var);

	return 0;
}


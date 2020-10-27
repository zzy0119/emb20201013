#include <stdio.h>

// 全局变量--->0
static int glob; // static  extern(默认)

int test(int n);
int main(void)
{
	// 局部变量--->值随机 auto(默认) static const register(寄存器变量) volatile(易失变量:防止编译优化)
	int var;
	const int n = 10; // 只读变量

	printf("%d\n", test(5));
	printf("%d\n", test(6));

	return 0;
}

int test(int n)
{
	static int a = 10; // 局部静态变量
	
	return n+a++;	
}



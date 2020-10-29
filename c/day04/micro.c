#include <stdio.h>

#define N	10

#define NUM	(2+2)

#define MULTI(m, n)	(m)*(n)

// 两个变量的交换 typeof(m) 获取m类型
#define SWAP2NUM(m, n) \
	do {\
		typeof(m) t; \
		t = m; \
		m = n; \
		n = t;\
	}while(0)

// 特殊符号 #(字符串类型) ## 连接
#define CONN(m, n) m##n
#define REP(x) #x

int main(void)
{
#if 0
	int a, b;

	for (int j = 0; j < N; j++) {
		for (int i = 0; i < N; i++) {
			printf("*");	
		}
		printf("\n");
	}

	a = 10; b = 5;
	printf("%d\n", MULTI(a+1, b+2));

	SWAP2NUM(a, b);

	printf("a:%d, b:%d\n", a, b);
#endif
#ifndef CONN // 条件编译
	int var = CONN(123, 678);
	printf("%d\n", var);
#endif

	printf("%s\n", REP(hello));

	printf("%d\n", NUM*NUM);// 2+2*2+2
	
	return 0;
}


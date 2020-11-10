#include <stdio.h>

typedef struct {
	char a;
	char d;
	int c;
	long b;
}test_t;

int main(void)
{
	test_t t;

	printf("%p, %p, %p, %p\n", &t.a, &t.d, &t.c, &t.b);
	printf("sizeof(t):%ld\n", sizeof(t));

	// 已知结构体中某个成员地址，求首地址
	printf("%d\n", (int)(&((test_t *)0)->c));

	return 0;
}

	

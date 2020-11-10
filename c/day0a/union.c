#include <stdio.h>

// 大端存储:低字节存高地址，高字节存低地址
// 小端存储:低字节存低地址，高字节存高地址

union test_un {
	char a;
	int b;
};

int main(void)
{
	union test_un t;

	t.b = 266;
	printf("sizeof(t):%ld\n", sizeof(t));

	printf("%d\n", t.a);

	t.b = 0x12345678;

	printf("%#x\n", t.a);

	return 0;
}


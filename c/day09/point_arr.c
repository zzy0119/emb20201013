#include <stdio.h>

// ./a.out 123

int main(int argc, char *argv[])
{
	char *arr[3] = {"西红柿鸡蛋", "蛋炒饭", "鸡蛋汤"}; // 指针数组

	for (int i = 0; i < argc; i++) {
		puts(argv[i]);
	}

	return 0;
}


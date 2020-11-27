#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char **environ;

static void test(void);
static void handler1(void)
{
	printf("%s is called\n", __FUNCTION__);
}

static void handler2(void)
{
	printf("%s is called\n", __FUNCTION__);
}

static void handler3(void)
{
	printf("%s is called\n", __FUNCTION__);
}

int main(void)
{
	atexit(handler1);
	atexit(handler2);
	atexit(handler3);

	// 打印环境变量
#if 0
	for (int i = 0; environ[i]; i++)
		puts(environ[i]);
#endif
	printf("%s\n", getenv("PATH"));
	setenv("PATH", ".", 1);
	printf("%s\n", getenv("PATH"));

	test();
	printf("after test\n");

	exit(EXIT_SUCCESS);
}

static void test(void)
{
	printf("hello world");
	exit(EXIT_FAILURE);
}



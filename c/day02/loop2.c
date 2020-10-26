#include <stdio.h>

int main(void)
{
	int n;
	int res = 0;

#if 0
	do {
		printf("输入一个整型数:");
		scanf("%d", &n);
	} while (n < 0);
#endif
RE_INPUT:
	printf("输入一个整型数:");
	scanf("%d", &n);
	if (n < 0)
		goto RE_INPUT;

	while (n > 0) {
		res += n;
		n --;
	}
	printf("res:%d\n", res);

#if 0
	while (1) {
	
	}

	for (;;) {
	
	}
#endif

	return 0;
}


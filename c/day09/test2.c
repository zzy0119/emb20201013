#include <stdio.h>

int main(int argc, char *argv[])
{
	int res = 0;
	int flag = 1;
	char *p;

	if (argc < 2)
		return 1;

	p = argv[1];
	if (*p == '-') {
		flag = -1;
		p++;
	}
	while (*p) {
		if (!(*p >= '0' && *p <= '9'))
			break;
		res = res * 10 + (*p-'0');
		p++;
	}
	printf("%d\n", res*flag);

	return 0;
}


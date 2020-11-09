#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	char *p;
	char *ret;

	if (argc < 3)
		return 1;

	p = argv[1];

	while (1) {
		ret = strsep(&p, " o");
		if (ret == NULL)
			break;
		if (strcmp(ret, "") == 0)
			continue;
		puts(ret);
	}

	return 0;
}


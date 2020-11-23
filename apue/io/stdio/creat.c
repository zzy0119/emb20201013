#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp = NULL;

	if (argc < 2)
		return 1;

	fp = fopen(argv[1], "w");
	if (NULL == fp)
		return 1;

	fputc('a', fp);
	fclose(fp);

	return 0;
}


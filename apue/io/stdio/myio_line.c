#include <stdio.h>

#define BUFSIZE	10

static int cpfile(FILE *rfp, FILE *wfp)
{
	char buf[BUFSIZE] = {};
	char *ret;

	while (1) {
		ret = fgets(buf, BUFSIZE, rfp);
		if (NULL == ret) {
			if (ferror(rfp))
				return -1;
			break;
		}
		fputs(buf, wfp);
	}

	return 0;
}

int main(int argc, char *argv[])
{
	FILE *fp = NULL;

	if (argc < 2)
		return 1;

	fp = fopen(argv[1], "r");
	if (NULL == fp) {
		printf("fopen() failed\n");
		return 1;
	}

	cpfile(fp, stdout);

	fclose(fp);

	return 0;
}


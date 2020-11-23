#include <stdio.h>

#define BUFSIZE	10

static int cpfile(FILE *rfp, FILE *wfp)
{
	char buf[BUFSIZE] = {};
	int cnt;

	while (1) {
		cnt = fread(buf, 1, BUFSIZE, rfp);
		if (cnt == 0) {
			if (feof(rfp))
				break;
			return -1;
		}
		fwrite(buf, 1, cnt, wfp);
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


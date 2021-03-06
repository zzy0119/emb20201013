#include <stdio.h>
#include <unistd.h>

static int cpfile(FILE *rfp, FILE *wfp)
{
	int ch;

	while (1) {
		ch = fgetc(rfp);	
		if (ch == EOF) {
			if (ferror(rfp))
				return -1;
			break;
		}
		fputc(ch, wfp);	
		sleep(1);
		fflush(NULL);
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
		fprintf(stderr, "fopen() failed\n");
		return 1;
	}

	cpfile(fp, stdout);

	fclose(fp);

	return 0;
}


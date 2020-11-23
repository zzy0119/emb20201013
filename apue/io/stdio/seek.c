#include <stdio.h>

int main(int argc, char *argv[])
{
	FILE *fp = NULL;
	char buf[10] = {};
	int cnt;

	if (argc < 2)
		return 1;

	fp = fopen(argv[1], "r");
	// if error

	fseek(fp, 10, SEEK_SET); // SEEK_END 末尾 SEEK_CUR
	cnt = fread(buf, 1, 10, fp);
	fwrite(buf, 1, cnt, stdout);

	printf("%ld\n", ftell(fp));

	rewind(fp);
	cnt = fread(buf, 1, 10, fp);
	fwrite(buf, 1, cnt, stdout);

	fclose(fp);

	return 0;
}


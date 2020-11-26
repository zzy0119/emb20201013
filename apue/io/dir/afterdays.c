#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define BUFSIZE	100

int main(int argc, char *argv[])
{
	time_t t;
	struct tm *tmp = NULL;
	char buf[BUFSIZE] = {};

	if (argc < 2)
		return 1;

	time(&t);
	tmp = localtime(&t);
	if (NULL == tmp)
		return 1;
	tmp->tm_mday += atoi(argv[1]);
	t = mktime(tmp);
	tmp = localtime(&t);

	strftime(buf, BUFSIZE, "%Y-%m-%d", tmp);
	puts(buf);

	return 0;
}


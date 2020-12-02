#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char cmd[512] = {};

	if (argc < 2)
		exit(1);

	snprintf(cmd, 512, "date > %s", argv[1]);

	system("clear");
	system(cmd);	

	exit(0);
}


#include <stdio.h>
#include <glob.h>

int main(int argc, char *argv[])
{
	glob_t res;

	if (glob("/etc/*", 0, NULL, &res) != 0)
		return 1;
	glob("/etc/.*", GLOB_APPEND, NULL, &res);

	for (int i = 0; i < res.gl_pathc; i++) 
		puts((res.gl_pathv)[i]);

	globfree(&res);

	return 0;
}


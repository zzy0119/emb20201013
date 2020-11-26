#include <stdio.h>
#include <dirent.h>
#include <errno.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
	DIR *dp = NULL;
	struct dirent *entry = NULL;

	if (argc < 2)
		return 1;

	dp = opendir(argv[1]);
	if (NULL == dp) {
		perror("opendir()");
		return 1;
	}

	while (1) {
		entry = readdir(dp);
		if (entry == NULL) {
			if (errno) {
				perror("readdir()");
				goto ERROR;
			}
			break;
		}
		puts(entry->d_name);
	}

	closedir(dp);

	return 0;
ERROR:
	closedir(dp);
	return 1;
}


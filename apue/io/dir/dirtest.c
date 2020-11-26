#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

#define PATHSIZE	128

static void showfiles(const char *path);
int main(int argc, char *argv[])
{
	if (argc < 2)
		return 1;

	showfiles(argv[1]);


	return 0;
}

static void showfiles(const char *path)
{
	struct stat res;
	DIR *dp = NULL;
	struct dirent *entry = NULL;
	char filepath[PATHSIZE] = {};

	stat(path, &res);
	if (!S_ISDIR(res.st_mode)) {
		puts(path);
		return;
	}

	dp = opendir(path);
	// if error
	while (1) {
		entry = readdir(dp);
		if (entry == NULL)
			break;
		if (!strcmp(entry->d_name, ".") || \
				!strcmp(entry->d_name, ".."))
			continue;
		memset(filepath, '\0', PATHSIZE);
		snprintf(filepath, PATHSIZE, "%s/%s", path, entry->d_name);
		showfiles(filepath);
	}

	closedir(dp);
}



#include <stdio.h>
#include <grp.h>
#include <pwd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

#define BUFSIZE	100

int main(int argc, char *argv[])
{
	struct stat res;

	if (argc < 2)
		return 1;

	if (stat(argv[1], &res) == -1) {
		perror("stat()");
		return 1;
	}

	// 类型
#if 0
	switch (res.st_mode & S_IFMT) {
		case S_IFREG:
			putchar('-');
			break;
		case S_IFDIR:
			putchar('d');
			break;
		default:
			break;
	}
#endif
	if (S_ISREG(res.st_mode)) {
		putchar('-');
	} else if (S_ISDIR(res.st_mode)) {
		putchar('d');
	}

	// 权限
	if (res.st_mode & S_IRUSR) {
		putchar('r');
	} else
		putchar('-');

	if (res.st_mode & S_IWUSR) {
		putchar('w');
	} else {
		putchar('-');
	}
	if (res.st_mode & S_IXUSR) {
		// 是否有u+s
		if (res.st_mode & S_ISUID)
			putchar('s');
		else
			putchar('x');
	} else {
		putchar('-');
	}

	// 硬链接
	printf(" %ld ", res.st_nlink);

	// 拥有者 所属组
	struct passwd *pwd = NULL;
	struct group *grp = NULL;

	pwd = getpwuid(res.st_uid);	
	if (NULL == pwd)
		return 1;
	printf("%s ", pwd->pw_name);
	
	grp = getgrgid(res.st_gid);
	if (NULL == grp)
		return 1;
	printf("%s ", grp->gr_name);

	// 文件字节大小
	printf("%ld ", res.st_size);

	// 文件时间 
	char tmbuf[BUFSIZE] = {};
	time_t t = res.st_mtime;
	struct tm *tmp = localtime(&t);
	strftime(tmbuf, BUFSIZE, "%m月 %d %H:%M", tmp);
	printf("%s ", tmbuf);

	printf("\n");
	return 0;
}


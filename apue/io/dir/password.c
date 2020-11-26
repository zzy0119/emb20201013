#include <stdio.h>
#include <string.h>
#include <shadow.h>
#include <unistd.h>

#define NAMESIZE	128

int main(void)
{
	char name[NAMESIZE] = {};
	char *pwd = NULL;
	struct spwd *sp = NULL;
	char *encryped = NULL;

	printf("用户名:");
	fgets(name, NAMESIZE, stdin);
	name[strlen(name)-1] = '\0';

	pwd = getpass("密码:");

	// 校验
	sp = getspnam(name);
	if (NULL == sp) {
		perror("getspnam()");
		return 1;
	}
	encryped = crypt(pwd, sp->sp_pwdp);
	if (encryped == NULL) {
		perror("crypt");
		return 1;
	}
	if (strcmp(sp->sp_pwdp, encryped) == 0) {
		printf("密码正确\n");
	} else {
		printf("鉴定错误\n");
	}

	return 0;
}


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "seq.h"

#define TELSIZE		12
#define NAMESIZE	32

enum {INSERT=1, SHOW=5, QUIT=9};

struct student_st {
	char name[NAMESIZE];
	char tel[TELSIZE];
	int age;
};

void clear_stdin(void);
static void pri_stu(const void *data)
{
	const struct student_st *d = data;
	printf("%32s %11s %2d\n", d->name, d->tel, d->age);
}

int main(void)
{
	manage_sys_t *mng = NULL;
	int choose;
	struct student_st s;

	manage_sys_init(&mng, sizeof(struct student_st));

	while (1) {
		system("clear");
		printf("欢迎登录学生管理系统\n");
		printf("1. 增加 5. 显示所有 9. 退出\n");
		scanf("%d", &choose);
		clear_stdin();
		if (choose == QUIT) {
			printf("再见!!!!!!!\n");
			break;
		}
		switch (choose) {
			case INSERT:
				printf("名字:");
				fgets(s.name, NAMESIZE, stdin);
				// 是否读到'\n'
				if ((s.name)[strlen(s.name)-1] == '\n')
					(s.name)[strlen(s.name)-1] = 0;
				else 
					clear_stdin();
				printf("电话:");
				fgets(s.tel, TELSIZE, stdin);
				if ((s.tel)[strlen(s.tel)-1] == '\n')
					(s.tel)[strlen(s.tel)-1] = '\0';
				else 
					clear_stdin();
				printf("年龄:");
				scanf("%d", &s.age);
				clear_stdin();
				manage_sys_add(mng, &s);
				break;
			case SHOW:
				manage_sys_traval(mng, pri_stu);
				sleep(2);
				break;
		}
	}

	return 0;
}

/*
 清理标准输入文件的数据
 */
void clear_stdin(void )
{
	char ch;
	do {
		ch = getchar();
	}while (ch != '\n');
}





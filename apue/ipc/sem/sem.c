/*
 调用进程创建"/tmp/out"文件，并写入0,然后创建20个子进程，20个子进程的工作都是将"/tmp/out"中的数据读出来，+1再写回去
 观察文件中最终的值为多少
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PROC_NR	20
#define FLPATH	"/tmp/out"
#define BUFSIZE	32

static int semid;

int rwfile(int fd);
int P(void);
int V(void);
int main(void)
{
	int fd;
	pid_t pid;

	fd = open(FLPATH, O_RDWR | O_CREAT | O_TRUNC, 0666);
	if (-1 == fd) {
		perror("open()");
		exit(1);
	}
	write(fd, "0", 1);

	// 初始化信号量数组
	semid = semget(IPC_PRIVATE, 1, IPC_CREAT | IPC_EXCL | 0600);
	if (-1 == semid) {
		perror("semget()");
		goto ERROR;
	}

	// 放信号
	semctl(semid, 0, SETVAL, 1);

	for (int i = 0; i < PROC_NR; i++) {
		pid = fork();
		// if error
		if (pid == 0) {
			rwfile(fd);	
			exit(0);
		}
	}

	for (int i = 0; i < PROC_NR; i++)
		wait(NULL);

	close(fd);

	exit(0);
ERROR:
	close(fd);
	exit(1);
}

int rwfile(int fd)
{
	char buf[BUFSIZE] = {};
	char tmp[BUFSIZE] = {};
		
	P(); // 取信号
	lseek(fd, 0, SEEK_SET);
	read(fd, buf, BUFSIZE);
	snprintf(tmp, BUFSIZE, "%d", atoi(buf)+1);
	lseek(fd, 0, SEEK_SET);
	write(fd, tmp, strlen(tmp));
	V(); // 还信号
	close(fd);

	return 0;
}

int P(void)
{
	struct sembuf buf;
	
	buf.sem_num = 0;
	buf.sem_op = -1;
	buf.sem_flg = 0;

	if (semop(semid, &buf, 1) == -1) {
		perror("semop()");
		return -1;
	}

	return 0;
}

int V(void)
{
	struct sembuf buf;
	
	buf.sem_num = 0;
	buf.sem_op = 1;
	buf.sem_flg = 0;

	if (semop(semid, &buf, 1) == -1) {
		perror("semop()");
		return -1;
	}

	return 0;
}


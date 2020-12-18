#include <stdio.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "proto.h"

#define MIN_FREE_PROCNR	3
#define MAX_FREE_PROCNR	5
#define MAX_PROC_POOL	30
#define NOTIFYSIG		SIGUSR2

enum {
	STATE_FREE = 1,
	STATE_BUSY, 
	STATE_BLANK=-1
};

typedef struct proc_st {
	int state; // 状态
	pid_t pid; // 子进程pid
}pool_t;


static int del_child_process(pool_t *pool);
int add_child_process(int sd, pool_t *pool);
static void sighandler(int s)
{
	;
}

int socket_init(in_port_t port)
{
	int sd;
	struct sockaddr_in laddr;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		return -1;
	}
	laddr.sin_family = AF_INET;
	inet_aton("0.0.0.0", &laddr.sin_addr);
	laddr.sin_port = htons(port);
	if (bind(sd, (void *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		close(sd);
		return -1;
	}
	listen(sd, 200);

	return sd;
}

int main(void)
{
	pool_t *pool;	
	int sd;
	struct sigaction act, oldact;
	sigset_t set, oldset;
	int freecnt, busycnt;

	pool = mmap(NULL, sizeof(pool_t)*MAX_PROC_POOL, \
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,\
			-1, 0);
	if (MAP_FAILED == pool) {
		perror("mmap()");
		exit(1);
	}

	// 初始化进程池
	for (int i = 0; i < MAX_PROC_POOL; i++) {
		pool[i].state = STATE_BLANK;
		pool[i].pid = -1;
	}

	// 初始化套接字
	sd = socket_init(SERVER_PORT);
	if (sd == -1) {
		goto ERROR;
	}

	// reuse addr
	int val = 1;
	setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val));

	// 注册信号的行为
	act.sa_handler = sighandler;
	act.sa_flags = 0;
	sigemptyset(&act.sa_mask);
	sigaction(NOTIFYSIG, &act, &oldact);
	// 子进程终止---》不变为僵尸
	act.sa_handler = SIG_DFL;
	act.sa_flags = SA_NOCLDWAIT;
	sigaction(SIGCHLD, &act, NULL);

	// 创建任务子进程
	for (int i = 0; i < MIN_FREE_PROCNR; i ++) {
		add_child_process(sd, pool);	
	}

	sigemptyset(&set);
	sigaddset(&set, NOTIFYSIG);
	sigprocmask(SIG_BLOCK, &set, &oldset);
	// 管理进程池
	while (1) {
		// 进程池中子进程状态变化	
		sigsuspend(&oldset);
		freecnt = 0;
		busycnt = 0;
		for (int i = 0; i < MAX_PROC_POOL; i++) {
			if (pool[i].state == STATE_BLANK && pool[i].pid == -1){
				putchar('-');
				continue;
			}
			if (pool[i].state == STATE_FREE) {
				putchar('X');
				freecnt ++;
			}
			else if (pool[i].state == STATE_BUSY) {
				putchar('O');
				busycnt ++;
			}
		}	
		printf("\n");
		if (freecnt < MIN_FREE_PROCNR) {
			add_child_process(sd, pool);
		}
		if (freecnt > MAX_FREE_PROCNR) {
			del_child_process(pool);
		}
	
	}

	exit(0);
ERROR:
	munmap(pool, sizeof(pool_t) * MAX_PROC_POOL);
	exit(1);
}

static int get_free_pos(const pool_t *pool)
{
	for (int i = 0; i < MAX_PROC_POOL; i++)
		if (pool[i].pid == -1 && pool[i].state == STATE_BLANK)
			return i;

	return -1;
}

// 子进程工作
static int child_job(int sd, pool_t *pool, int pos)
{
	struct sockaddr_in client_addr;
	socklen_t client_addrlen;
	int newsd;

	client_addrlen = sizeof(client_addr);
	while (1) {
		pool[pos].state = STATE_FREE;
		kill(getppid(), NOTIFYSIG);
		newsd = accept(sd, (void *)&client_addr, &client_addrlen);
		if (newsd == -1) {
			if (errno == EINTR)
				continue;
			perror("accept()");
			return -1;
		}
		pool[pos].state = STATE_BUSY;	
		kill(getppid(), NOTIFYSIG);

		sleep(3);
		write(newsd, "hello", 5);
		close(newsd);
	}
}

// 添加任务进程
int add_child_process(int sd, pool_t *pool)
{
	int pos = 0;
	pid_t pid;

	pos = get_free_pos(pool);
	if (pos == -1) {
		return -1;
	}

	pid = fork();
	if (pid == -1) {
		return -1;
	}
	if (pid == 0) {
		// 子进程
		child_job(sd, pool, pos);
		exit(0);
	}
	pool[pos].pid = pid;
	pool[pos].state = STATE_FREE;

	return 0;
}

static int del_child_process(pool_t *pool)
{
	for (int i = 0; i < MAX_PROC_POOL; i++) {
		if (pool[i].pid > 0 && pool[i].state == STATE_FREE) {
			kill(pool[i].pid, SIGTERM);	
			pool[i].pid = -1;
			pool[i].state = STATE_BLANK;
			return 0;
		}
	}

	return -1;
}




#include <stdio.h>
#include <stdlib.h>

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
	sigset_t set;

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
			if (pool[i].state == STATE_BLANK && pool[i].pid == -1)
				continue;
			if (pool[i].state == STATE_FREE)
				freecnt ++;
			else if (pool[i].state == STATE_BUSY)
				busycnt ++;
		}	
		if (freecnt < MIN_FREE_PROCNR) {
			add_child_process();
		}
		if (freecnt > MAX_FREE_PROCNR) {
			del_child_process();
		}
	
	}

	exit(0);
ERROR:
	munmap(pool, sizeof(pool_t) * MAX_PROC_POOL);
	exit(1);
}


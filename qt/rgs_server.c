#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <sqlite3.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "proto.h"

static int socket_init(int *sd);
int main(void)
{
	int sd;
	sqlite3 *db = NULL;
	int ret;
	char *errmsg = NULL; 
	struct rgs_st rcvbuf;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;

	socket_init(&sd);
	
	// 创建数据库
	ret = sqlite3_open("/home/emb1013/code20201013/emb20201013/qt/nettalk.db", &db);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_open() failed\n");
		goto OPEN_ERROR;
	}

	// 创建注册表
	ret = sqlite3_exec(db, \
			"create table if not exists rgsTable(\
			count text primary key not null, \
			password text not null);",\
		  NULL, NULL, &errmsg);
	if (ret != SQLITE_OK) {
		fprintf(stderr, "sqlite3_exec():%s\n", errmsg);
		goto EXEC_ERROR;
	}
	sqlite3_close(db);

#if 1
	// 等待接受客户端注册请求
	client_addr_len = sizeof(client_addr);
	while (1) {
		cnt = recvfrom(sd, &rcvbuf, sizeof(rcvbuf), 0, \
				(struct sockaddr *)&client_addr, &client_addr_len);	
		if (cnt == -1) {
			perror("recvfrom()");
			goto OPEN_ERROR;
		}
		
		pid = fork();	
		if (pid == 0) {
			// 判断此帐号是否可以注册
			ret = isRgsOk(rcvbuf);
			if (ret == -1) {
				fprintf(stderr, "isRgsOk() failed");
				exit(1);
			}
			if (ret == RGS_OK) {
				rcvbuf.rgs_stat = RGS_OK;
			} else if (ret == RGS_ALREADY) {
				rcvbuf.rgs_stat = RGS_ALREADY;
			}
			sendto(sd, &rcvbuf, sizeof(rcvbuf), (void *)&client_addr, \
					client_addr_len);
		}

	}
#endif

	exit(0);
EXEC_ERROR:
	sqlite3_close(db);
OPEN_ERROR:
	close(sd);
	exit(1);
}

static int socket_init(int *sd)
{
	struct sockaddr_in laddr;

	*sd = socket(AF_INET, SOCK_DGRAM, 0);
	if(-1 == *sd){
		perror("socket()");
		return -1;
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(RGS_SERVERPORT);
	inet_aton("0.0.0.0", &laddr.sin_addr);
	if (bind(*sd, (struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	return 0;

ERROR:
	close(*sd);
	return -1;
}

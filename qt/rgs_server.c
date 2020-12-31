#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include "proto.h"

int main(void)
{
	int sd;

	socket_init();
	
	// 创建数据库
	sqlite3_open();

	// 创建注册表
	sqlite3_exec();

	// 等待接受客户端注册请求
	while (1) {
		recvfrom();	
		
		pid = fork();	
		if (pid == 0) {
			// 判断此帐号是否可以注册
		}

	}

	exit(0);
}



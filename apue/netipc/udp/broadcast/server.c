#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <arpa/inet.h>

#include "proto.h"

int main(void)
{
	int sd;
	int flag;
	struct sockaddr_in baddr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	// 设置为广播套接字
	flag = 1;
	if (setsockopt(sd, SOL_SOCKET, SO_BROADCAST, &flag, sizeof(flag)) == -1) {
		perror("setsockopt()");
		goto ERROR;
	}

	baddr.sin_family = AF_INET;
	baddr.sin_addr.s_addr = INADDR_BROADCAST;
	baddr.sin_port = htons(RCVPORT);
	while (1) {
		sendto(sd, "good afternoon", 14, 0, (void *)&baddr, \
				sizeof(baddr));
		sleep(1);
	}

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}


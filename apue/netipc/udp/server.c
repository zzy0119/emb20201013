#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "proto.h"

int main(void)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddrlen;
	char buf[MAXMSG] = {};
	
	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(SERVERPROT); // 本地字节序转网络字节序
	inet_aton(SERVERIP, &laddr.sin_addr);
	if (bind(sd, (struct sockaddr *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto BINDERROR;
	}

	raddrlen = sizeof(raddr); // !!!!
	while (1) {
		memset(buf, '\0', MAXMSG);
		if (recvfrom(sd, buf, MAXMSG, 0, (struct sockaddr *)&raddr, &raddrlen) == -1) {
			perror("recvfrom()");
			goto BINDERROR;
		}

		if (strcmp(buf, "EXIT") == 0)
			break;
		printf("message from ip:%s, port:%d\n", \
				inet_ntoa(raddr.sin_addr), ntohs(raddr.sin_port));
		printf("message:%s\n", buf);
	}

	close(sd);

	exit(0);
BINDERROR:
	close(sd);
	exit(1);
}


#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include "proto.h"

int main(void)
{
	int sd;
	struct ip_mreqn imq;
	struct sockaddr_in raddr;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	// 设置多播选项
	inet_aton(MULTICASTIP, &imq.imr_multiaddr);
	// inet_aton("0.0.0.0", imq.imr_address);
	imq.imr_address.s_addr = INADDR_ANY;
	imq.imr_ifindex = if_nametoindex("ens33");	
	if (setsockopt(sd, IPPROTO_IP, IP_MULTICAST_IF, &imq, sizeof(imq)) == -1) {
		perror("setsockopt()");
		goto ERROR;
	}

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(RECVPORT);
	inet_aton(MULTICASTIP, &raddr.sin_addr);
	while (1) {
		sendto(sd, "hello", 5, 0, (void *)&raddr, sizeof(raddr));	
		sleep(1);
	}

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}

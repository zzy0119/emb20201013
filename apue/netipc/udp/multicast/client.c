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
	struct sockaddr_in laddr, raddr;
	socklen_t raddrlen;
	struct ip_mreqn imq;
	char buf[MAXMSG] = {};
	int cnt;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(RECVPORT);
	inet_aton("0.0.0.0", &laddr.sin_addr);
	if (bind(sd, (void *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	inet_aton(MULTICASTIP, &imq.imr_multiaddr);
	inet_aton("0.0.0.0", &imq.imr_address);
	imq.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &imq, sizeof(imq)) == -1) {
		perror("setsockopt()");
		goto ERROR;
	}

	raddrlen = sizeof(raddr);
	cnt = recvfrom(sd, buf, MAXMSG, 0, (void *)&raddr, &raddrlen);
	if (cnt == -1) {
		perror("recvfrom()");
		goto ERROR;
	}
	printf("ip:%s, port:%d\n", inet_ntoa(raddr.sin_addr), \
			ntohs(raddr.sin_port));
	printf("data:%s\n", buf);

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}


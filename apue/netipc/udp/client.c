#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in raddr; 

	if (argc < 2)
		exit(1);

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	// if error
	// bind()

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(SERVERPROT);
	inet_aton(SERVERIP, &raddr.sin_addr);
	sendto(sd, argv[1], strlen(argv[1]), 0, \
			(void *)&raddr, sizeof(raddr));

	close(sd);

	exit(0);
}


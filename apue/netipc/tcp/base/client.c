#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	int sd;
	struct sockaddr_in server_addr;
	msg_t sndbuf;

	if (argc < 3)
		exit(0);

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(SERVERPORT);
	inet_aton(SERVERIP, &server_addr.sin_addr);
	if (connect(sd, (void *)&server_addr, sizeof(server_addr)) == -1) {
		perror("connect()");
		goto ERROR;
	}

	sndbuf.id = atoi(argv[1]);
	strncpy(sndbuf.name, argv[2], NAMESIZE);
	write(sd, &sndbuf, sizeof(sndbuf));

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(0);
}


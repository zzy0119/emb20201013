#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "proto.h"

int main(void)
{
	int sd;
	struct sockaddr_un raddr;
	socklen_t len;

	sd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (sd == -1) {
		perror("socket()");
		exit(0);
	}

	raddr.sun_family = AF_UNIX;
	strncpy(raddr.sun_path, PATHNAME, 108);
	len = (int)(&((struct sockaddr_un *)0)->sun_path)+strlen(raddr.sun_path)+1;
	sendto(sd, "hello", 5, 0, (void *)&raddr, len);

	close(sd);

	exit(0);
}


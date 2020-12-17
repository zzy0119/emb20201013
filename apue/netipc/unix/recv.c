#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/un.h>

#include "proto.h"

int main(void)
{
	int sd;
	struct sockaddr_un laddr, raddr;
	socklen_t raddrlen;
	char buf[MAXMSG] = {};
	socklen_t len;

	sd = socket(AF_UNIX, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	laddr.sun_family = AF_UNIX;
	strncpy(laddr.sun_path, PATHNAME, 108);
	len = (int)(&((struct sockaddr_un *)0)->sun_path)+strlen(laddr.sun_path)+1;
	if (bind(sd, (void *)&laddr, len) == -1) {
		perror("bind()");
		goto ERROR;
	}

	raddrlen = sizeof(struct sockaddr_un);
	recvfrom(sd, buf, MAXMSG, 0, (void *)&raddr, &raddrlen);
	puts(buf);

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}


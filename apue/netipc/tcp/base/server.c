#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>          /* See NOTES */
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "proto.h"

int main(void)
{
	int sd, newsd;
	struct sockaddr_in local_addr, remote_addr;
	socklen_t remote_addrlen;
	msg_t rcvbuf;
	pid_t pid;

	sd = socket(AF_INET, SOCK_STREAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	local_addr.sin_family = AF_INET;
	local_addr.sin_addr.s_addr = INADDR_ANY;
	local_addr.sin_port = htons(SERVERPORT);
	if (bind(sd, (void *)&local_addr, sizeof(local_addr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	if (listen(sd, 30) == -1) {
		perror("listen()");
		goto ERROR;
	}

	remote_addrlen = sizeof(remote_addr);
	while (1) {
		newsd = accept(sd, (void *)&remote_addr, &remote_addrlen);
		pid = fork();
		// if error
		if (pid == 0) {
			read(newsd, &rcvbuf, sizeof(rcvbuf));		
			printf("%d %s\n", rcvbuf.id, rcvbuf.name);
			close(newsd);
			exit(0);
		}
	}

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(0);
}


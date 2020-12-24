#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#include "../include/proto.h"

int main(void)
{
	int sd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddrlen;
	struct ip_mreqn imq;
	char buf[MAXMSG] = {};
	int cnt;
	chn_list_t *rcvlist;
	list_entry_t *entry;
	int choose;
	chn_data_t *rcvdata;
	int pfd[2];
	pid_t pid;

	sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == sd) {
		perror("socket()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(RCVPORT);
	inet_aton("0.0.0.0", &laddr.sin_addr);
	if (bind(sd, (void *)&laddr, sizeof(laddr)) == -1) {
		perror("bind()");
		goto ERROR;
	}

	inet_aton(GROUPADDR, &imq.imr_multiaddr);
	inet_aton("0.0.0.0", &imq.imr_address);
	imq.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &imq, sizeof(imq)) == -1) {
		perror("setsockopt()");
		goto ERROR;
	}

	rcvlist = malloc(MAXMSG);

	while (1) {
		cnt = recvfrom(sd, rcvlist, MAXMSG, 0, NULL, NULL);	
		if (cnt == -1) {
			perror("recvfrom()");
			goto ERROR;
		}
		if (rcvlist->chnid != 0)		
			continue;
		else // 列表		
			break;
	}

	for (entry = rcvlist->entry; entry < (char *)rcvlist+cnt; )
	{
		printf("%d %s\n", entry->chnid, entry->descr);
		entry = (char *)entry+entry->len;
	}

	printf("请选择频道:");
	scanf("%d", &choose);

	if (pipe(pfd) == -1) {
		perror("pipe()");
		exit(1);
	}

	pid = fork();
	if (pid == -1) {
		perror("fork()");
		goto ERROR;
	}

	if (pid == 0) {
		close(pfd[1]);
		dup2(pfd[0], 0);
		close(pfd[0]);
		execlp("mplayer", "mplayer", "-cache", "8192", "-", NULL);
		perror("execlp()");
		exit(1);
	}

	close(pfd[0]);

	rcvdata = malloc(MAXMSG);
	while (1) {
		cnt = recvfrom(sd, rcvdata, MAXMSG, 0, NULL, NULL);
		if (cnt == 0) {
			perror("rcvfrom()");
			goto ERROR;
		}
		if (rcvdata->chnid != choose)	
			continue;
		write(pfd[1], rcvdata->data, cnt-1);
	}

	close(sd);

	exit(0);
ERROR:
	close(sd);
	exit(1);
}


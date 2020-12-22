#include <stdio.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <net/if.h>
#include <unistd.h>

#include "medialib.h"
#include "thr_chnlist.h"
#include "thr_chn.h"
#include "../include/proto.h"

static int socket_init(int *sd);
int main(void)
{
	medlib_chnlist_t *ml = NULL;
	int n = 0;
	int sd;

	socket_init(&sd);

	medialib_getchnlist(&ml, &n);

	for (int i = 0; i < n; i++) {
		printf("%d %s\n", ml[i].chnid, ml[i].descr);
	}

	thr_chnlist_create(sd, ml, n);

#if 0
	for (int i = 0; i < n; i++)	{
		thr_chn_create(ml[i].chnid);
	}
#endif

	while (1)
		pause();

	exit(0);
}

static int socket_init(int *sd)
{
	struct ip_mreqn imr;

	*sd = socket(AF_INET, SOCK_DGRAM, 0);
	if (-1 == *sd) {
		perror("socket()");
		return -1;
	}
	
	inet_aton(GROUPADDR, &imr.imr_multiaddr);
	inet_aton("0.0.0.0", &imr.imr_address);
	imr.imr_ifindex = if_nametoindex("ens33");
	if (setsockopt(*sd, IPPROTO_IP, IP_MULTICAST_IF, &imr, sizeof(imr)) == -1) {
		perror("setsockopt()");
		close(*sd);
		return -1;
	}
}







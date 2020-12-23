#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>

#include "../include/proto.h"
#include "medialib.h"

struct thr_chn_st {
	int sd;
	int8_t chnid;
};

static struct thr_chn_st chnst;

static void *thr_chn(void *s)
{
	chn_data_t *snd = NULL;
	int ret;
	struct sockaddr_in raddr;

	snd = malloc(MAXMSG);	
	if (NULL == snd)
		pthread_exit(NULL);
	snd->chnid = chnst.chnid;

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(RCVPORT);
	inet_aton(GROUPADDR, &raddr.sin_addr);
	while (1) {
		ret = medialib_readchn(chnst.chnid, snd->data, MAXMSG-1);
		if (ret == -1)
			break;
		sendto(chnst.sd, snd, ret+1, 0, (void *)&raddr, sizeof(raddr));
		sleep(1);
	}

	pthread_exit(NULL);
}

int thr_chn_create(int sd, int8_t chnid)
{
	pthread_t tid;
	int err;

	chnst.sd = sd;
	chnst.chnid = chnid;

	err = pthread_create(&tid, NULL, thr_chn, NULL);
	if (err) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));
		return -1;
	}
}


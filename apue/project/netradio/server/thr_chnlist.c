#include <pthread.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include "thr_chnlist.h"
#include "../include/proto.h"

typedef struct {
	int sd;
	medlib_chnlist_t *chnlist;
	int nmembs;
}thr_list_t;

static thr_list_t list;
static void *thr_list(void *arg)
{
	chn_list_t *snd;	
	list_entry_t *entry;
	int size = 0;
	int i;
	struct sockaddr_in raddr;

	size = sizeof(chnid_t); // 0
	// 所有频道描述的总字节个数
	for (i = 0; i < list.nmembs; i++) {
		size += sizeof(int8_t)*2; // chnid+len;
		size += (strlen((list.chnlist)[i].descr)+1);
	}
	snd = malloc(size);
	// if error
	snd->chnid = 0;
	entry = (void *)((char *)snd+sizeof(chnid_t));
	i = 0;
	while (i < list.nmembs) {
		entry->chnid = (list.chnlist)[i].chnid;	
		strcpy(entry->descr, (list.chnlist)[i].descr);
		entry->len = sizeof(int8_t)*2+strlen(entry->descr)+1;
		i++;
		entry = (void *)((char *)entry+entry->len);
	}

	raddr.sin_family = AF_INET;
	raddr.sin_port = htons(RCVPORT);
	inet_aton(GROUPADDR, &raddr.sin_addr);
	while (1) {
		if (sendto(list.sd, snd, size, 0, (void *)&raddr, sizeof(raddr)) == -1) {
			perror("sendto()");
			pthread_exit(NULL);
		}
		sleep(1);
	}

}

int thr_chnlist_create(int sd, medlib_chnlist_t *mlib, int n)
{
	pthread_t tid;
	int err;

	list.sd = sd;
	list.chnlist = mlib;
	list.nmembs = n;

	err = pthread_create(&tid, NULL, thr_list, NULL);
	if (err) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));
		return -1;
	}
	return 0;
}


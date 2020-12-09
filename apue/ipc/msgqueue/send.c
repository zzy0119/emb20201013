#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "proto.h"

int main(int argc, char *argv[])
{
	key_t key;
	int msgid;
	int created = 1;
	msg_t sndbuf;	

	if (argc < 3)
		exit(1);

	key = ftok(PATHNAME, PRO_ID);
	if (-1 == key) {
		perror("ftok()");
		exit(1);
	}
	msgid = msgget(key, IPC_CREAT | IPC_EXCL | 0600);
	if (-1 == msgid) {
		if (errno == EEXIST) {
			msgid = msgget(key, 0);
			created = 0;
		} else {
			perror("msgget()");
			exit(1);
		}
	}

	// 发数据
	sndbuf.mtype = atoi(argv[1]);
	strncpy(sndbuf.msg, argv[2], MSGSIZE);
	msgsnd(msgid, &sndbuf, strlen(argv[2])+1, 0);

	if (created)
		msgctl(msgid, IPC_RMID, NULL);

	return 0;
ERROR:
	if (created)
		msgctl(msgid, IPC_RMID, NULL);

	exit(1);
}


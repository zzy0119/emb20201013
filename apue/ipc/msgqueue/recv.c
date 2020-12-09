#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include "proto.h"

int main(void)
{
	key_t key;
	int msgid;
	int created = 1;
	msg_t rcvbuf;	

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

	while (1) {
		if (msgrcv(msgid, &rcvbuf, sizeof(msg_t)-sizeof(long), 2, 0) == -1) {
			perror("msgrcv()");
			goto ERROR;
		}
		if (!strcmp(rcvbuf.msg, "exit"))
			break;
		puts(rcvbuf.msg);
	}

	if (created)
		msgctl(msgid, IPC_RMID, NULL);

	return 0;
ERROR:
	if (created)
		msgctl(msgid, IPC_RMID, NULL);

	exit(1);
}


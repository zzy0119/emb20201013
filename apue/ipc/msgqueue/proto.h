#ifndef __PROTO_H
#define __PROTO_H

#define PATHNAME	"/etc/passwd"
#define PRO_ID		1
#define MSGSIZE		1024

// 数据格式
typedef struct {
	long mtype; // > 0
	char msg[MSGSIZE];
}msg_t;

#endif


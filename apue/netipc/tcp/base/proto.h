#ifndef __PTOTO_H
#define __PTOTO_H

#define SERVERIP		"10.10.10.177"
#define SERVERPORT	1213

// #pragma pack(1)

#define NAMESIZE	32

struct stu{
	uint8_t id;
	char name[NAMESIZE];
}__attribute__((packed));

typedef struct stu msg_t;

#endif


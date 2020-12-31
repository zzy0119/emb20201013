#ifndef __NETTALK_PROT_H
#define __NETTALK_PROT_H

#define RGS_SERVERIP	"192.168.1.23"
#define RGS_SERVERPORT	9988

#define COUNT_SIZE		32
#define PWD_SIZE		128
enum {
	RGS_OK,
	RGS_ALREADY
};

struct rgs_st {
	char count[COUNT_SIZE];
	char password[PWD_SIZE];
	int8_t rgs_stat;
}__attribute__((packed));

#endif


#ifndef __NETRADIO_PROTO_H
#define __NETRADIO_PROTO_H

#pragma pack(1)

#define GROUPADDR	"234.2.3.4"
#define RCVPORT		1234

#define MAXMSG		512

#define CHNLISTID	0		// 频道列表id
#define CHNMINID	1		// 起始频道id
#define CHNNR		200 	// 总频道个数
#define CHNMAXID	(CHNNR)-(CHNMINID)+1 // 最大频道id

// 频道列表
typedef int8_t chnid_t;
// 每一个频道
typedef struct {
	chnid_t chnid; // MUST BE > 0
	int8_t len; // 整个结构字节个数
	char descr[1];
}list_entry_t;

typedef struct {
	chnid_t chnid; // MUST BE 0
	list_entry_t entry[1];
}chn_list_t;

// 数据
typedef struct {
	chnid_t chnid;
	char data[1];
}chn_data_t;

#endif


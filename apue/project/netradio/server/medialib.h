#ifndef __MEDIALIB_H
#define __MEDIALIB_H

#include <stdint.h>

#define MEDIAPATH	"./medias"

typedef struct chnlist_st {
	int8_t chnid;
	char *descr;
}medlib_chnlist_t;

/*
 获取频道列表
 *mlib是结构的首地址
 *n成员个数
 */
int medialib_getchnlist(medlib_chnlist_t **mlib, int *n);

/*
	获取频道数据
*/

ssize_t medialib_readchn(int8_t chnid, void *buf, size_t size);

#endif



#include "../include/proto.h"
#include "medialib.h"

struct context_st {
	int8_t id;
	char *descr;
	glob_t map3path;
	int curindex;
	int fd;
	int pos;
};

static struct context_st *chn_contexts[CHNNR+1];

// 获取给定频道路径的频道信息结构
// "./medias/channel1"
struct context_st *get_chn_context(const char *path)
{


}

int medialib_getchnlist(medlib_chnlist_t **mlib, int *n)
{


}


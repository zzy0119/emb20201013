#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <glob.h>
#include <fcntl.h>

#include "../include/proto.h"
#include "medialib.h"

#define BUFSIZE	128

struct context_st {
	int8_t id;
	char *descr;
	glob_t mp3path;
	int curindex;
	int fd;
	int pos;
};

static struct context_st *chn_contexts[CHNNR+1];

// 获取给定频道路径的频道信息结构
// "./medias/channel1"
struct context_st *get_chn_context(const char *path)
{
	static int8_t id = 1;
	struct context_st *c;
	char buf[BUFSIZE] = {};
	FILE *fp;

	c = malloc(sizeof(*c));
	if (NULL == c)
		return NULL;
	c->id = id++;

	c->curindex = 0;

	strncpy(buf, path, BUFSIZE);
	strncat(buf, "/descr.txt", BUFSIZE);
	fp = fopen(buf, "r");
	if (NULL == fp) {
		free(c);
		return NULL;
	}
	memset(buf, '\0', BUFSIZE);
	fgets(buf, BUFSIZE, fp);
	c->descr = strdup(buf);

	//path/*.mp3
	memset(buf, '\0', BUFSIZE);
	strncpy(buf, path, BUFSIZE);
	strncat(buf, "/*.mp3", BUFSIZE);
	glob(buf, 0, NULL, &c->mp3path);
	if (c->mp3path.gl_pathc != 0) {
		c->fd = open((c->mp3path.gl_pathv)[0], O_RDONLY);
		if (c->fd == -1) {
			perror("open()");
			goto ERROR;
		}
		c->pos = 0;
	} else {
		// printf("无效频道\n");
		free(c);
		id--;
		return NULL;
	}

	return c;

ERROR:
	free(c);
	free(c->descr);
	return NULL;
}

int medialib_getchnlist(medlib_chnlist_t **mlib, int *n)
{
	char buf[BUFSIZE] = {};
	glob_t res;
	struct context_st *ret;
	int i;

	strncpy(buf, MEDIAPATH, BUFSIZE);
	strncat(buf, "/*", BUFSIZE);

	glob(buf, 0, NULL, &res);

	*mlib = calloc(res.gl_pathc, sizeof(medlib_chnlist_t));

	for (i = 0; i < res.gl_pathc; i++) {
		ret = get_chn_context((res.gl_pathv)[i]);
		if (ret == NULL)
			continue;
		chn_contexts[ret->id] = ret;
		(*mlib)[i].chnid = ret->id;
		(*mlib)[i].descr = ret->descr;
		printf("chn fd:%d\n", chn_contexts[ret->id]->fd);
	}
	*n = i;

	return 0;
}

// 打开下一个文件
static int open_next(int8_t chnid)
{
	chn_contexts[chnid]->curindex = (chn_contexts[chnid]->curindex+1) % chn_contexts[chnid]->mp3path.gl_pathc;

	close(chn_contexts[chnid]->fd);
	chn_contexts[chnid]->fd = open((chn_contexts[chnid]->mp3path.gl_pathv)[chn_contexts[chnid]->curindex], O_RDONLY);
	if (-1 == chn_contexts[chnid]->fd)
		return -1;
	return 0;
}


ssize_t medialib_readchn(int8_t chnid, void *buf, size_t size)
{
	int cnt;
	while (1) {
		cnt = pread(chn_contexts[chnid]->fd, buf, size, chn_contexts[chnid]->pos);
		if (cnt == -1) {
			perror("pread()");
			return -1;
		}
		if (cnt == 0) {
			// 当前文件读完了，读下一个文件
			open_next(chnid);	
			chn_contexts[chnid]->pos = 0;
			printf("%d\n", chn_contexts[chnid]->fd);
		} else {
			// 读到了
			chn_contexts[chnid]->pos += cnt;
			break;
		}
	}

	return cnt;
}








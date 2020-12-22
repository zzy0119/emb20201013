#include <stdio.h>
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
		printf("无效频道\n");
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
		chn_contexts[ret->id] = ret;
		(*mlib)[i].chnid = ret->id;
		(*mlib)[i].descr = ret->descr;
	}
	*n = i;

	return 0;
}








#ifndef __LIST_H
#define __LIST_H

enum {INSERT_HEAD, INSERT_TAIL};

// 结点数据类型
struct node_st {
	void *data;
	struct node_st *next; //后继结点地址
};

// 头结点
typedef struct {
	struct node_st node;
	int size;
}head_t;

typedef void (*print_t)(const void *data);
typedef int (*cmp_t)(const void *data, const void *key);

int head_init(head_t **h, int size);

int list_insert(head_t *h, const void *data, int way);

int list_delete(head_t *h, const void *key, cmp_t cmp);

void *list_search(const head_t *h, const void *key, cmp_t cmp);

void list_traval(const head_t *h, print_t pri);

void list_destroy(head_t *h);

#endif


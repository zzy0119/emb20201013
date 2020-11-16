#ifndef __LLIST_H
#define __LLIST_H

enum {HEADINSERT, TAILINSERT};

// 双向环链
struct node_st {
	struct node_st *prev;
	struct node_st *next;
	char data[0];
};

typedef struct {
	struct node_st node;
	int size;
}llisthead_t;

typedef int (*cmp_t)(const void *data, const void *key);

int llisthead_init(llisthead_t **h, int size);

int llist_insert(llisthead_t *h, const void *data, int way);

void llist_traval(const llisthead_t *h, void (*pr)(const void *));

void llist_destroy(llisthead_t *h);

int llist_delete(llisthead_t *h, const void *key, cmp_t cmp);

void *llist_search(const llisthead_t *h, const void *key, cmp_t cmp);

#endif


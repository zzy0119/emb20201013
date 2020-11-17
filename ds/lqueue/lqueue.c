#include <stdio.h>

#include "lqueue.h"

int lqueue_init(lqueue_t **lq, int size)
{
	return llisthead_init(lq, size);
}

int lqueue_empty(const lqueue_t *lq)
{
	return llist_empty(lq);
}

int lqueue_enq(lqueue_t *lq, const void *data)
{
	return llist_insert(lq, data, TAILINSERT);
}

static int alway_cmp(const void *data, const void *key)
{
	return 0;
}

int lqueue_deq(lqueue_t *lq, void *data)
{
	return llist_fetch(lq, NULL, alway_cmp, data);
}

void lqueue_destroy(lqueue_t *lq)
{
	llist_destroy(lq);
}

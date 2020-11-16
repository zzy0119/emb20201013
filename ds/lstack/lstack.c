#include <stdio.h>
#include "lstack.h"

int lstack_init(lstack_t **ls, int size)
{
	return llisthead_init(ls, size);
}

int lstack_push(lstack_t *ls, const void *data)
{
	return llist_insert(ls, data, HEADINSERT);
}

static int always_cmp(const void *data, const void *key)
{
	return 0;
}

int lstack_pop(lstack_t *ls, void *data)
{
	return llist_fetch(ls, NULL, always_cmp, data);
}

int lstack_empty(const lstack_t *ls)
{
	return llist_empty(ls);
}

void lstack_destroy(lstack_t *ls)
{
	llist_destroy(ls);
}


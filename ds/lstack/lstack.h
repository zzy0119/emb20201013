#ifndef __LSTATCK_H
#define __LSTATCK_H

#include <llist.h>

typedef llisthead_t lstack_t;

int lstack_init(lstack_t **ls, int size);

int lstack_push(lstack_t *ls, const void *data);

int lstack_pop(lstack_t *ls, void *data);

int lstack_empty(const lstack_t *ls);

void lstack_destroy(lstack_t *ls);

#endif


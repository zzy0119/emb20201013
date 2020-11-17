#ifndef __LQUEUE_H
#define __LQUEUE_H

#include <llist.h>

typedef llisthead_t lqueue_t;

int lqueue_init(lqueue_t **lq, int size);

int lqueue_empty(const lqueue_t *lq);

int lqueue_enq(lqueue_t *lq, const void *data);

int lqueue_deq(lqueue_t *lq, void *data);

void lqueue_destroy(lqueue_t *lq);

#endif


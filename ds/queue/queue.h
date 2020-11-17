#ifndef __QUEUE_H
#define __QUEUE_H

typedef struct {
	void *base;
	int front;
	int tail;
	int size;
	int nmembs;
}queue_t;

int queue_init(queue_t **q, int size, int nmembs);

int queue_empty(const queue_t *q);

int queue_full(const queue_t *q);

int enq(queue_t *q, const void *data);

int deq(queue_t *q, void *data);

void queue_destroy(queue_t *q);

#endif


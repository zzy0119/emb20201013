#include <string.h>
#include <stdlib.h>
#include "queue.h"

int queue_init(queue_t **q, int size, int nmembs)
{
	*q = malloc(sizeof(queue_t));
	if (NULL == *q)
		return -1;
	(*q)->base = calloc(size, nmembs);
	if (NULL == (*q)->base) {
		free(*q);
		return -1;
	}
	(*q)->front = (*q)->tail = 0;
	(*q)->size = size;
	(*q)->nmembs = nmembs;

	return 0;
}

int queue_empty(const queue_t *q)
{
	return q->front == q->tail;
}

int queue_full(const queue_t *q)
{
	return (q->tail + 1) % q->nmembs == q->front;
}

int enq(queue_t *q, const void *data)
{
	if (queue_full(q))
		return -1;
	memcpy((char *)q->base + q->tail*q->size, \
			data, q->size);
	q->tail = (q->tail + 1) % q->nmembs;

	return 0;
}

int deq(queue_t *q, void *data)
{
	if (queue_empty(q))
		return -1;
	memcpy(data, (char *)q->base+q->front*q->size, \
			q->size);
	q->front = (q->front+1) % q->nmembs;

	return 0;
}

void queue_destroy(queue_t *q)
{
	free(q->base);
	free(q);
}


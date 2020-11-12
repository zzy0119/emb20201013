#include <stdlib.h>
#include <string.h>

#include "llist.h"

int llisthead_init(llisthead_t **h, int size)
{
	*h = malloc(sizeof(llisthead_t));
	if (NULL == *h)
		return -1;
	(*h)->size = size;
	(*h)->node.data = NULL;
	(*h)->node.prev = (*h)->node.next = &(*h)->node;

	return 0;
}

static void _insert(struct node_st *new, struct node_st *prev, struct node_st *next)
{
	new->next = next;
	new->prev = prev;
	prev->next = new;
	next->prev = new;
}

int llist_insert(llisthead_t *h, const void *data, int way)
{
	struct node_st *new;

	new = malloc(sizeof(struct node_st));
	if (NULL == new)
		return -1;
	new->data = malloc(h->size);
	if (NULL == new->data) {
		free(new);
		return -1;
	}
	memcpy(new->data, data, h->size);

	if (way == HEADINSERT) {
		_insert(new, &h->node, h->node.next);
	} else if (way == TAILINSERT) {
		_insert(new, h->node.prev, &h->node);
	} else {
		free(new->data);
		free(new);
		return -1;
	}

	return 0;
}

void llist_traval(const llisthead_t *h, void (*pr)(const void *))
{
	struct node_st *cur;

	for(cur = h->node.next; cur != &h->node; cur = cur->next) {
		pr(cur->data);
	}

}

void llist_destroy(llisthead_t *h) 
{
	struct node_st *cur;	
	
	cur = h->node.next;
	while (cur != &h->node) {
		h->node.next = cur->next;
		cur->next->prev = &h->node;
		cur->prev = cur->next = NULL;
		free(cur->data);
		free(cur);
		cur = h->node.next;
	}	
	free(h);
}

static struct node_st *find_node(const llisthead_t *h, \
		const void *key, cmp_t cmp)
{
	struct node_st *cur;

	for (cur = h->node.next; cur != &h->node; cur = cur->next) {
		if (!cmp(cur->data, key))
			return cur;
	}
	return NULL;
}

static void _delete(struct node_st *del)
{
	del->prev->next = del->next;
	del->next->prev = del->prev;

	del->next = del->prev = NULL;
	free(del->data);
	free(del);
}

int llist_delete(llisthead_t *h, const void *key, cmp_t cmp)
{
	struct node_st *cur;	

	cur = find_node(h, key, cmp);
	if (NULL == cur) 
		return -1;
	_delete(cur);

	return 0;
}

void *llist_search(const llisthead_t *h, const void *key, cmp_t cmp)
{
	struct node_st *cur;

	cur = find_node(h, key, cmp);
	if (NULL == cur)
		return NULL;

	return cur->data;
}



#include <stdlib.h>
#include <string.h>
#include "list.h"

int head_init(head_t **h, int size)
{
	*h = malloc(sizeof(head_t));
	if (NULL == *h)
		return -1;
	(*h)->node.data = NULL;
	(*h)->node.next = &(*h)->node;
	(*h)->size = size;

	return 0;
}

int list_insert(head_t *h, const void *data, int way)
{
	struct node_st *new;	
	struct node_st *p;

	new = calloc(1, sizeof(struct node_st));
	if (NULL == new)
		return -1;
	new->data = malloc(h->size);
	if (NULL == new) {
		free(new);
		return -1;
	}
	memcpy(new->data, data, h->size);

	if (way == INSERT_HEAD) {
		new->next = h->node.next;
		h->node.next = new;
	} else if (way == INSERT_TAIL){
		for (p=h->node.next; p->next!=&h->node; p=p->next)	
			;
		p->next = new;
		new->next = &h->node;
	}

	return 0;
}

void list_traval(const head_t *h, print_t pri)
{
	struct node_st *p;

	for (p=h->node.next; p!=&h->node; p = p->next)
		pri(p->data);
}

void list_destroy(head_t *h)
{
	struct node_st *cur, *nx;

	cur = h->node.next;

	while (cur != &h->node) {
		nx = cur->next;
		free(cur);
		cur = nx;
	}

	free(h);
	h = NULL;
}

static struct node_st *find_pre(const head_t *h, const void *key, cmp_t cmp)
{
	struct node_st *pre, *n;

	pre = (struct node_st *)&h->node;
	n = pre->next;
	while (n != &h->node) {
		if (!cmp(n->data, key))
			return pre;
		pre = n;
		n = n->next;
	}
	return NULL;
}

int list_delete(head_t *h, const void *key, cmp_t cmp)
{
	struct node_st *pre, *del;

	pre = find_pre(h, key, cmp);
	if (NULL == pre)
		return -1;
	del = pre->next;
	pre->next = del->next;
	del->next = NULL;
	free(del->data);
	free(del);

	return 0;
}

void *list_search(const head_t *h, const void *key, cmp_t cmp)
{
	struct node_st *pre = find_pre(h, key, cmp);
	if (NULL == pre)
		return NULL;
	return pre->next->data;
}

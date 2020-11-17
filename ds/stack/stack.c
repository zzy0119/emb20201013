#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "stack.h"

int stack_init(stack_t **s, int size, int nmembers)
{
	*s = malloc(sizeof(stack_t));
	if (NULL == *s)
		return -1;
	(*s)->base = calloc(nmembers, size);
	if (NULL == (*s)->base) {
		free(*s);
		return -1;
	}
	(*s)->top = (*s)->base;
	(*s)->size = size;
	(*s)->nmembers = nmembers;

	return 0;
}

int stack_empty(const stack_t *s)
{
	return s->base == s->top;
}

int stack_full(const stack_t *s)
{
	return ((char *)s->top-(char *)s->base) / s->size == s->nmembers;
}

int push(stack_t *s, const void *data)
{
	if (stack_full(s))
		return -1;
	memcpy(s->top, data, s->size);
	s->top = (char *)s->top + s->size;

	return 0;
}

int pop(stack_t *s, void *data)
{
	if (stack_empty(s)) {
		return -1;
	}
	s->top = (char *)s->top - s->size;
	memcpy(data, s->top, s->size);

	return 0;
}

void stack_destroy(stack_t *s)
{
	free(s->base);
	free(s);
}

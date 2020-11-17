#ifndef __STACK_H
#define __STACK_H

typedef struct {
	void *base;
	void *top;
	int size;
	int nmembers;
}stack_t;

int stack_init(stack_t **s, int size, int nmembers);

int stack_empty(const stack_t *s);

int stack_full(const stack_t *s);

int push(stack_t *s, const void *data);

int pop(stack_t *s, void *data);

void stack_destroy(stack_t *s);

#endif


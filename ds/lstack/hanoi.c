#include <stdio.h>
#include "lstack.h"

static int step = 0;
// 汉诺塔问题
static int move(lstack_t *src, lstack_t *dest)
{
	char ch;
	if (lstack_empty(src))
		return -1;
	lstack_pop(src, &ch);
	lstack_push(dest, &ch);

	step ++;

	return 0;
}

static int hanoi(lstack_t *a, lstack_t *c, lstack_t *b, int n)
{
	if (n == 1) {
		move(a, c);
		return 0;
	} else if (n < 1)
		return -1;
	hanoi(a, b, c, n-1);
	hanoi(a, c, b, 1);
	hanoi(b, c, a, n-1);
}

int main(void)
{
	lstack_t *posta, *postb, *postc;	
	char ch;

	lstack_init(&posta, sizeof(char));
	lstack_init(&postb, sizeof(char));
	lstack_init(&postc, sizeof(char));

	for (int i = 0; i < 10; i++) {
		ch = 'A' + i;	
		lstack_push(posta, &ch);
	}

	hanoi(posta, postc, postb, 10);

	printf("steps:%d\n", step);

	lstack_destroy(posta);
	lstack_destroy(postb);
	lstack_destroy(postc);

	return 0;
}


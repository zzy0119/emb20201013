#include <stdio.h>

#include "queue.h"

int main(int argc, char *argv[])
{
	queue_t *q;
	char *p;
	char ch;
	
	if (argc < 2)
		return 1;

	queue_init(&q, sizeof(char), 10);

	p = argv[1];
	while (*p) {
		enq(q, p);
		p++;
	}
	while (!queue_empty(q)) {
		deq(q, &ch);
		putchar(ch);
	}
	putchar('\n');
	
	queue_destroy(q);

	return 0;
}


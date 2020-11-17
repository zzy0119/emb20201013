#include <stdio.h>

#include "lqueue.h"

int main(int argc, char *argv[])
{
	lqueue_t *q;
	int i;
	char ch;

	if (argc < 2)
		return -1;

	lqueue_init(&q, sizeof(char));

	i = 0;
	while (argv[1][i]) {
		lqueue_enq(q, argv[1]+i);
		i++;
	}

	while (!lqueue_empty(q)) {
		lqueue_deq(q, &ch);
		putchar(ch);
	}
	putchar('\n');

	lqueue_destroy(q);

	return 0;
}


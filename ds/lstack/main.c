#include <stdio.h>

#include "lstack.h"

int main(int argc, char *argv[])
{
	lstack_t *l = NULL;
	int i = 0;
	char ch;

	if (argc < 2)
		return 1;

	lstack_init(&l, sizeof(char));

	
	while (argv[1][i]) {
		lstack_push(l, argv[1]+i);
		i++;
	}

	while (!lstack_empty(l)) {
		lstack_pop(l, &ch);
		putchar(ch);
	}

	lstack_destroy(l);

	return 0;
}


#include <stdio.h>
#include <stdlib.h>

#include "list.h"

static void show(const void *data)
{
	const int *d = data;

	printf("%d ", *d);
}

int main(int argc, char *argv[])
{
	head_t *head;
	int n;

	head_init(&head, sizeof(int));

	for (int i = 1; i < argc; i++) {
		n = atoi(argv[i]);
		list_insert(head, &n, INSERT_TAIL);
	}
	list_traval(head, show);	
	printf("\n");

	list_destroy(head);

	return 0;
}


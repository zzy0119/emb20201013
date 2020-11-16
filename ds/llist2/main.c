#include <stdio.h>

#include <llist.h>

static void show_data(const void *data)
{
	const char *d = data;
	printf("%c\n", *d);
}

static int cmpchar(const void *data, const void *key)
{
	const char *d = data;
	const char *k = key;

	return *d - *k;
}

int main(int argc, char *argv[])
{
	llisthead_t *head = NULL;
	int i;
	char ch;

	if (argc < 2)
		return 1;

	llisthead_init(&head, sizeof(char));

	i = 0;
	while (argv[1][i]) {
		llist_insert(head, argv[1]+i, TAILINSERT);
		i++;
	}
	llist_traval(head, show_data);

	printf("***************************\n");
	ch = 'w';
	llist_delete(head, &ch, cmpchar);
	llist_traval(head, show_data);

	llist_destroy(head);

	return 0;
}


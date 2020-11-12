#include <stdio.h>
#include <stdlib.h>

#include "list.h"

static void show(const void *data)
{
	const int *d = data;

	printf("%d ", *d);
}

static int cmpn(const void *data, const void *key)
{
	const int *d = data;
	const int *k = key;

	return *d - *k;
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

	printf("************************************\n");
	n = atoi(argv[2]);
	list_delete(head, &n, cmpn);
	list_traval(head, show);	
	printf("\n");

	printf("************************************\n");
	n = 8;
	int *f = list_search(head, &n, cmpn);
	if (NULL == f)
		printf("没有值为%d的元素\n", n);
	else {
		printf("找到了:%d\n", *f);
	}

	list_destroy(head);

	return 0;
}


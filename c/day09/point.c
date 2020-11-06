#include <stdio.h>
#include <stdlib.h>

int addElment(int **p, int *n, int elm);
int main(void)
{
	int *arr = NULL;
	int n = 0;

	addElment(&arr, &n, 1);
	addElment(&arr, &n, 101);
	addElment(&arr, &n, 10);
	addElment(&arr, &n, 29);

	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");

	free(arr);
	arr = NULL;

	return 0;
}

/*
 向动态数组中增加指定元素
 */ 
int addElment(int **p, int *n, int elm)
{
	*p = realloc(*p, (*n+1)*sizeof(int));
	if (NULL == *p)
		return -1;
	(*p)[*n] = elm;
	(*n)++;

	return 0;
}




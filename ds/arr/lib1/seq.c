#include <stdlib.h>
#include <string.h>
#include "seq.h"

int manage_sys_init(manage_sys_t **m, int size)
{
	*m = malloc(sizeof(manage_sys_t));
	if (NULL == *m)
		return -1;
	(*m)->arr = NULL;
	(*m)->nmember = 0;
	(*m)->size = size;

	return 0;
}

int manage_sys_add(manage_sys_t *m, const void *data)
{
	m->arr = realloc(m->arr, (m->nmember+1)*m->size);	
	if (NULL == m->arr)
		return -1;
	memcpy((char *)m->arr+m->nmember*m->size, data, m->size);
	m->nmember++;

	return 0;
}

void manage_sys_traval(const manage_sys_t *m, pri_t pri)
{
	for (int i = 0; i < m->nmember; i++)
		pri((char *)m->arr+i*m->size);
}




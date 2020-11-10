#ifndef __SEQ_H
#define __SEQ_H

/*
 数据结构增删改查
 */
// 抽象数据类型 ADT
typedef struct {
	void *arr;
	int nmember;
	int size;
}manage_sys_t;

typedef void (*pri_t)(const void *data);

// manage_sys_t *manage_sys_init(int size);
int manage_sys_init(manage_sys_t **m, int size);

int manage_sys_add(manage_sys_t *m, const void *data);

void manage_sys_traval(const manage_sys_t *m, pri_t pri);

#endif


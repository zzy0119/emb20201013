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
int (*cmp_t)(const void *data, const void *key);

// manage_sys_t *manage_sys_init(int size);
/*
初始化创建管理系统结构
m:回填开辟管理系统结构的地址到*m
size:存储数据的大小
 */
int manage_sys_init(manage_sys_t **m, int size);

/*
 增加一个数据
m:管理系统结构的地址
data:待插入元素的地址
 */
int manage_sys_add(manage_sys_t *m, const void *data);

/*
 遍历所有成员
m:管理系统结构的地址(只读)
pri:打印函数 根据成员地址打印
 */
void manage_sys_traval(const manage_sys_t *m, pri_t pri);

int manage_sys_del(manage_sys_t *m, const void *key, cmp_t cmp);

void *manage_sys_search(const manage_sys_t *m, const void *key, cmp_t cmp);

void manage_sys_free(manage_sys_t *m);

#endif


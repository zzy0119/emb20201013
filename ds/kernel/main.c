#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "list.h"

#define NAMESIZE	32

struct stu_st {
	char name[NAMESIZE];
	int id;
	struct list_head node;
};

int main(void)
{
	int ids[] = {3, 1, 6, 7, 9, 2, 4, 5, 8};
	struct stu_st *s;
	struct list_head *p;

	LIST_HEAD(head);
		
	for (int i = 0; i < sizeof(ids) / sizeof(*ids); i++) {
		s = malloc(sizeof(struct stu_st));	
		// if error
		s->id = ids[i];
		snprintf(s->name, NAMESIZE, "stu%d", i+1);
		list_add_tail(&s->node, &head);
	}

	// 遍历
	list_for_each(p, &head) {
		s = list_entry(p, struct stu_st, node);		
		printf("%s %d\n", s->name, s->id);
	}	

	printf("***********************************\n");
	// 删除 "stu5"
	list_for_each(p, &head) {
		s = list_entry(p, struct stu_st, node);
		if (strcmp(s->name, "stu5") == 0) {
			list_del(&s->node);
			free(s);
			break;
		}
	}
	list_for_each(p, &head) {
		s = list_entry(p, struct stu_st, node);		
		printf("%s %d\n", s->name, s->id);
	}	

	return 0;
}


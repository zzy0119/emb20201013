#include <stdio.h>

#include "stack.h"

int main(int argc, char *argv[])
{
	stack_t *s = NULL;
	char *p;
	char ch;

	if (argc < 2)
		return 1;

	stack_init(&s, sizeof(char), 10);

	p = argv[1];
	while (*p) {
		if (push(s, p) == -1) {
			printf("栈已满！\n");
			break;
		}
		p++;
	}

	while (!stack_empty(s)) {
		pop(s, &ch);
		putchar(ch);
	}
	putchar('\n');

	stack_destroy(s);

	return 0;
}


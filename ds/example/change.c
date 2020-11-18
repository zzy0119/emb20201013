#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stack.h>
#include <queue.h>

char *midToLast(const char *p);
int main(int argc, char *argv[])
{
	char *r;
	if (argc < 2)
		return 1;

	r = midToLast(argv[1]);
	if (r == NULL) {
		printf("表达式有误\n");
	} else {
		puts(r);
	}

	return 0;
}

static int opValue(char ch)
{
	if (ch == '+' || ch == '-')
		return 1;
	else if (ch == '*' || ch == '/')
		return 2;

	return -1;
}

char *midToLast(const char *p)
{
	stack_t *s;
	queue_t *q;
	int len;
	char ch;
	char *res = NULL;
	int i;

	len = strlen(p);

	stack_init(&s, sizeof(char), len);
	queue_init(&q, sizeof(char), len+1);

	while (*p) {
		if (*p >= '0' && *p <= '9')
			enq(q, p);
		else if (*p == '(') 
			push(s, p);
		else if (*p == ')') {
			while (1) {
				if (pop(s, &ch) == -1) {
					goto ERROR;
				}
				if (ch == '(')
					break;
				enq(q, &ch);
			}
		} else if (*p == '+' || *p == '-' || \
				*p == '*' || *p == '/') {
			while (!stack_empty(s)) {
				pop(s, &ch);
				if (opValue(ch) < opValue(*p)) {
					push(s, &ch);
					break;
				}
				enq(q, &ch);
			}
			push(s, p);
		} else
			goto ERROR;
		p++;
	}

	while (!stack_empty(s)) {
		pop(s, &ch);
		enq(q, &ch);
	}

	i = 0;
	while (!queue_empty(q)) {
		deq(q, &ch);
		res = realloc(res, i+1);
		res[i] = ch;
		i++;
	}

	stack_destroy(s);
	queue_destroy(q);
	return res;

ERROR:
	stack_destroy(s);
	queue_destroy(q);
	return NULL;
}



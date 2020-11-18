#include <stdio.h>
#include <stack.h>
#include <queue.h>

#define N	27

static int seq_ball(queue_t **ball) 
{
	queue_t *tmpq = NULL;
	char t = 0, cur;
	int ret = 1;	

	queue_init(&tmpq, sizeof(char), N+1);

	while (!queue_empty(*ball)) {
		deq(*ball, &cur);
		if (cur < t) {
			// 不是依次1~27
			ret = 0;	
		}
		t = cur;
		enq(tmpq, &cur);
	}
	queue_destroy(*ball);
	*ball = tmpq;	

	return ret;
}

int main(void)
{
	queue_t *ball = NULL;
	stack_t *one_min = NULL;
	stack_t *five_min = NULL;
	stack_t *one_hour = NULL;
	char i, tmp;
	int days = 0;

	queue_init(&ball, sizeof(char), N+1);
	stack_init(&one_min, sizeof(char), 4);
	stack_init(&five_min, sizeof(char), 11);
	stack_init(&one_hour, sizeof(char), 11);

	for (i = 1; i <= N; i++) {
		enq(ball, &i);	
	}

	while (1) {
		deq(ball, &i);
		if (!stack_full(one_min)) {
			push(one_min, &i);
		} else {
			while (!stack_empty(one_min)) {
				pop(one_min, &tmp);
				enq(ball, &tmp);
			}
			if (!stack_full(five_min)) {
				push(five_min, &i);
			} else {
				while (!stack_empty(five_min)) {
					pop(five_min, &tmp);
					enq(ball, &tmp);
				} 
				if (!stack_full(one_hour)) {
					push(one_hour, &i);
				} else {
					while (!stack_empty(one_hour)) {
						pop(one_hour, &tmp);
						enq(ball, &tmp);
					}
					enq(ball, &i); // 12hours
					days ++;
					if (seq_ball(&ball)) {
						break;
					}
				}
			}
		}
	}

	printf("经过%d天\n", days / 2);

	return 0;
}


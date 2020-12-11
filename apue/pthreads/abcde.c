#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define THRNR	5

static int curid = 0;
static pthread_mutex_t mut;

void *thrfun(void *s);
int main(void)
{
	pthread_t tids[THRNR] = {};
	int err;

	alarm(5);

	pthread_mutex_init(&mut, NULL);
	for (int i = 0; i < THRNR; i++) {
		err = pthread_create(tids+i, NULL, thrfun, (void *)i);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}

	for (int i = 0; i < THRNR; i = (i+1) % THRNR) {
		pthread_mutex_lock(&mut);
		while (curid != -1) {
			pthread_mutex_unlock(&mut);
			sched_yield();
			pthread_mutex_lock(&mut);
		}
		curid = i;
		pthread_mutex_unlock(&mut);
	}

	exit(0);
}

// 任务线程
void *thrfun(void *s)
{
	int myid = (int)s;

	while (1) {
		pthread_mutex_lock(&mut);
		if (curid == -1) {
			pthread_mutex_unlock(&mut);
			sched_yield();
			continue;
		}

		if (curid != myid) {
			pthread_mutex_unlock(&mut);
			sched_yield();
			continue;
		}
		putchar('a'+myid);
		curid = -1;
		pthread_mutex_unlock(&mut);
	}

}






#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sched.h>

#define THRNR	4
#define START	100
#define END		300

static int job; // 0任务未发放  >0 所发放的任务 -1所有任务发放完成
// job多线程竞争
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static int isPrimer(int n);
static void *thr_fun(void *s);
int main(void)
{
	pthread_t tids[THRNR] = {};	
	int err;

	for (int i = 0; i < THRNR; i++)	 {
		err = pthread_create(tids+i, NULL, thr_fun, NULL);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}

	// 任务的发放
	for (int i = START; i <= END; i++) {
		pthread_mutex_lock(&mut);
		while (job != 0) {
			pthread_cond_wait(&cond, &mut);
		}
		job = i;
		pthread_cond_signal(&cond);
		pthread_mutex_unlock(&mut);
	}

	pthread_mutex_lock(&mut);
	while (job > 0) {
		pthread_cond_wait(&cond, &mut);
	}
	job = -1;
	pthread_cond_broadcast(&cond);
	pthread_mutex_unlock(&mut);

	for (int i = 0; i < THRNR; i++)
		pthread_join(tids[i], NULL);

	pthread_mutex_destroy(&mut);
	pthread_cond_destroy(&cond);

	exit(0);
}

static void *thr_fun(void *s)
{
	int num;

	while (1) {
		pthread_mutex_lock(&mut);	
		while (job == 0) {
			pthread_cond_wait(&cond, &mut);
		}
		if (job == -1) {
			pthread_mutex_unlock(&mut);
			pthread_exit(NULL);
		}
		num = job;
		job = 0;
		pthread_cond_broadcast(&cond);
		pthread_mutex_unlock(&mut);

		if (isPrimer(num))
			printf("%d是质数\n", num);
	}
}

static int isPrimer(int n)
{
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return 0;
	return 1;
}








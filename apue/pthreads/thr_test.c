/*
 100~300之间的质数输出
 一个数值对应一个线程，201数值同时计算
 */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>

#define START	100
#define END		300

#define THRNR	201

static void *thr(void *s);
int main(void)
{
	pthread_t tids[THRNR] = {};
	int err;

	for (int i = START; i <= END; i++) {
		err = pthread_create(tids+i-START, NULL, thr, (void *)i);
		if (err) {
			fprintf(stderr, "pthread_create():%s\n", strerror(err));
			exit(1);
		}
	}

	for (int i = 0; i < THRNR; i++) 
		pthread_join(tids[i], NULL);

	exit(0);
}

static int isPrimer(int n)
{
	for (int i = 2; i < n; i++)
		if (n % i == 0)
			return 0;
	return 1;
}

static void *thr(void *s)
{
	int num = s;

	// sleep(1);

	if (isPrimer(num))	{
		printf("%d\n", num);
	}

	pthread_exit(NULL);
}





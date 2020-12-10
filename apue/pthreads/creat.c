#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

static void *thr(void *s)
{
	for (int i = 0; i < 10; i++) {
		write(1, "!", 1);
		sleep(1);
	}

	// return (void *)0; // 启动例程返回
	pthread_exit((void *)0);
}

int main(void)
{
	pthread_t tid;
	int err;

	if (err = pthread_create(&tid, NULL, thr, NULL)) {
		fprintf(stderr, "pthread_create():%s\n", strerror(err));	
		exit(1);
	}

	// 等待新线程终止
	pthread_join(tid, NULL);

	while (1) {
		write(1, "*", 1);
		sleep(1);
	}

	exit(0);
}


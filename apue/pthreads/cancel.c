#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>


static void exit_handler1(void *arg)
{
	printf("%s is called\n", __FUNCTION__);
}

static void exit_handler2(void *arg)
{
	printf("%s is called\n", __FUNCTION__);
}

static void exit_handler3(void *arg)
{
	printf("%s is called\n", __FUNCTION__);
}

static void *thrfun(void *arg)
{
	pthread_cleanup_push(exit_handler1, NULL);
	pthread_cleanup_push(exit_handler2, NULL);
	pthread_cleanup_push(exit_handler3, NULL);

	for (int i = 0; i < 10; i++) {
		write(1, "*", 1);
		sleep(1);
	}

	pthread_exit(NULL);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
	pthread_cleanup_pop(0);
}

int main(void)
{
	pthread_t tid;
	int err;

	pthread_create(&tid, NULL, thrfun, NULL);
	// if error
	pthread_detach(tid); // 分离

	for (int i = 0; i < 3; i++) {
		write(1, "!", 1);
		sleep(1);
	}
	// pthread_cancel(tid);

#if 0
	if (err = pthread_join(tid, NULL)) {
		fprintf(stderr, "pthread_join():%s\n", strerror(err));
		exit(1);
	}
#endif
	
	pthread_exit(0);
}


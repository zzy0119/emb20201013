#include <stdio.h>
#include <string.h>
#include <signal.h>
#include <stdlib.h>
#include <pthread.h>

static int flag;
static pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

static sigset_t set;

static void *thrfun(void *s)
{
	int signo, err;

	while (1) {
		if (err = sigwait(&set, &signo)) {
			fprintf(stderr, "sigwait():%s\n", strerror(err));
			exit(1);
		}
		switch (signo) {
			case SIGINT:
				printf("SIGINT is comming\n");
				break;
			case SIGQUIT:
				pthread_mutex_lock(&mut);
				flag = 1;
				pthread_cond_signal(&cond);
				pthread_mutex_unlock(&mut);
				break;
			default:
				break;
		}
	}
}	

int main(void)
{
	pthread_t tid;
	sigset_t oldset;

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);

	pthread_sigmask(SIG_BLOCK, &set, &oldset);

	pthread_create(&tid, NULL, thrfun, NULL);
	// if error;

	pthread_mutex_lock(&mut);
	while (flag == 0) {
		pthread_cond_wait(&cond, &mut);
	}
	pthread_mutex_unlock(&mut);
	
	printf("got it\n");

	pthread_sigmask(SIG_SETMASK, &oldset, NULL);
	pthread_mutex_destroy(&mut);
	pthread_cond_destroy(&cond);

	exit(0);
}


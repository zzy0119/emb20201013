#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static void sig_handler(int s)
{
	for (int i = 0; i < 3; i++) {
		write(1, "!", 1);
		sleep(1);
	}
}
static void sig_handler2(int s)
{
	write(1, "&", 1);
}

int main(void)
{
	sigset_t set, oldset;
	struct sigaction act1, oldact1;

//	signal(SIGINT, sig_handler);
	act1.sa_handler = sig_handler;
	act1.sa_flags = 0;
	sigemptyset(&act1.sa_mask);
	sigaddset(&act1.sa_mask, SIGQUIT);
	sigaction(SIGINT, &act1, &oldact1);
	signal(SIGQUIT, sig_handler2);

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);

	for (int row = 0; row < 10; row++) {
		sigprocmask(SIG_BLOCK, &set, &oldset);
		for (int n = 0; n < 5; n++) {
			write(1, "*", 1);
			sleep(1);
		}
		write(1, "\n", 1);
		sigprocmask(SIG_UNBLOCK, &set, NULL);
	}

	exit(0);
}


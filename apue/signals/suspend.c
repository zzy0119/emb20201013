#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static void sig_handler(int s)
{
	write(1, "!", 1);
}

int main(void)
{
	sigset_t set, oldset;

	signal(SIGINT, sig_handler);
	signal(SIGQUIT, sig_handler);
	signal(SIGRTMIN, sig_handler);
	signal(SIGRTMIN+1, sig_handler);

	sigemptyset(&set);
	sigaddset(&set, SIGINT);
	sigaddset(&set, SIGQUIT);
	sigaddset(&set, SIGRTMIN);
	sigaddset(&set, SIGRTMIN+1);

	sigprocmask(SIG_BLOCK, &set, &oldset);
	for (int row = 0; row < 10; row++) {
		for (int n = 0; n < 5; n++) {
			write(1, "*", 1);
			sleep(1);
		}
		write(1, "\n", 1);
		sigsuspend(&oldset);
	}

	exit(0);
}


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void handler(int s)
{
	for (int i = 0; i < 3; i++) {
		printf("%d", s);
		fflush(NULL);
		write(1, "*", 1);
		sleep(1);
	}
}

int main(void)
{
	void (*ret)(int);
	int i = 0;

	ret = signal(SIGINT, handler);
	signal(SIGQUIT, handler);

	while (1) {
		write(1, "!", 1);
		sleep(10);
		i++;
		if (i == 10)
			signal(SIGINT, ret);
	}

	exit(0);
}


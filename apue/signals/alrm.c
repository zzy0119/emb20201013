#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

static int arr[4][4] = {
	{0, 1, 0, 0},
	{0, 1, 1, 0},
	{0, 0, 1, 0},
	{0, 0, 0, 0}
};
static int row = 1, col = 1;

static void show()
{
	system("clear");
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (arr[i][j]) {
				printf("\33[%d;%dH[]", row+i, j*2+col);
				fflush(NULL);
			}
		}
	}
}

static void alrm_handler(int s)
{
//	alarm(1);
	row++;
	show();
}

int main(void)
{
	struct itimerval itm;

	signal(SIGALRM, alrm_handler);
// 	alarm(1);
	itm.it_interval.tv_sec = 0;
	itm.it_interval.tv_usec = 500000;
	itm.it_value.tv_sec = 2;
	itm.it_value.tv_usec = 500000;

	setitimer(ITIMER_REAL, &itm, NULL);

	while (1)
		;

	exit(0);
}


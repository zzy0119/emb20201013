#include <stdio.h>
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
	alarm(1);
	row++;
	show();
}

int main(void)
{
	signal(SIGALRM, alrm_handler);
	alarm(1);

	while (1)
		;

	exit(0);
}


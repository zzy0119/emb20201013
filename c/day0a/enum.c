#include <stdio.h>

enum {RED, BLUE, YELLOW=9, WHITE, BLACK};

int main(void)
{

	printf("%d, %d, %d, %d, %d\n", \
			RED, BLUE, YELLOW, WHITE, BLACK);

	return 0;
}


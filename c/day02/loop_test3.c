#include <stdio.h>

int main(void)
{
	int i;

	for (i = 1; i <= 100; i++) {
		if (i % 3 == 0 && i % 5 == 0) {
			printf("%d同时能被3和5整除\n", i);
		}
	}

	return 0;
}

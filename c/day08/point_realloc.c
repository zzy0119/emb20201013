#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	char ch;
	char *p = NULL;
	int i;

	i = 0;
	do {
		scanf("%c", &ch);		
		if (ch == '\n')
			break;
		p = realloc(p, (i+1)*sizeof(char));
		p[i++] = ch;
	}while(1);

	puts(p);
	free(p);
	p = NULL;

	return 0;
}


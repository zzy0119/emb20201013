#include <stdio.h>
#include <stdlib.h>

#include "medialib.h"
#include "thr_chnlist.h"
#include "thr_chn.h"

int main(void)
{
	medlib_chnlist_t *ml = NULL;
	int n = 0;

	socket_init();

	medialib_getchnlist(&ml, &n);

	thr_chnlist_create(ml, n);

	for (int i = 0; i < n; i++)	{
		thr_chn_create(ml[i].chnid);
	}

	while (1)
		pause();

	exit(0);
}


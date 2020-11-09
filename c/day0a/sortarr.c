#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int (*cmp_t)(const void *data1, const void *data2);

void sort_arr(void *arr, int nmemb, int size, cmp_t cmp);

static int cmp_string(const void *data1, const void *data2)
{
	char *const*d1 = data1;
	char *const*d2 = data2;

	return strcmp(*d1, *d2);
}

int main(int argc, char *argv[])
{
	sort_arr(argv, argc, sizeof(char *), cmp_string);

	for (int i = 0; i < argc; i++)
		puts(argv[i]);

	return 0;
}

static void myqsort(void *arr, int low, int high, int size, cmp_t cmp)
{
	int first, last;
	void *key;

	if (low >= high)
		return ;

	first = low;
	last = high;

	key = malloc(size);	

//	key = arr[first];
	memcpy(key, (char *)arr+first*size, size);
	while (first < last) {
		while (cmp(key, (char *)arr+last*size) <= 0 && \
				first < last)
			last --;
	// 	arr[first] = arr[last];
		memcpy((char *)arr+first*size, \
				(char *)arr+last*size, size);
		while (cmp(key, (char *)arr+first*size) >= 0 && \
				first < last)
			first ++;
		// arr[last] = arr[fist];
		memcpy((char *)arr+last*size,\
				(char *)arr+first*size, size);
		printf("first:%d, last:%d\n", first, last);
	}
	memcpy((char *)arr+first*size, key, size);
	free(key);
	key = NULL;

	myqsort(arr, low, first-1, size, cmp);
	myqsort(arr, first+1, high, size, cmp);

}

void sort_arr(void *arr, int nmemb, int size, cmp_t cmp)
{
	myqsort(arr, 0, nmemb-1, size, cmp);
}


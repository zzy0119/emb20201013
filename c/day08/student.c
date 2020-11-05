#include <stdio.h>
#include <stdlib.h>

#define ADD		1
#define DEL		2
#define TRAVAL	7
#define QUIT	9

int *add_score(int *arr, int *nmemb, int score);
int *del_score(int *arr, int *nmemb, int del);
void arr_traval(int *arr, int n);
int main(void)
{
	int choose;	
	int n;
	int *a = NULL;
	int memb = 0;

	while (1) {
		printf("1.增加 2.删除 7.查看 9.退出\n");
		scanf("%d", &choose);
		if (choose == QUIT)
			break;
		switch (choose) {
			case ADD:
				printf("输入新成绩:");
				scanf("%d", &n);
				a = add_score(a, &memb, n);
				break;
			case DEL:
				printf("输入待删除的元素:");
				scanf("%d", &n);
				a = del_score(a, &memb, n);
				break;
			case TRAVAL:
				arr_traval(a, memb);
				break;
		}
	}

	return 0;
}

int *add_score(int *arr, int *nmemb, int score)
{
	arr = realloc(arr, (*nmemb+1)*sizeof(int));	
	if (NULL == arr)
		return NULL;
	arr[*nmemb] = score;
	(*nmemb) ++;

	return arr;
}

int *del_score(int *arr, int *nmemb, int del)
{
	int i;
	for ( i = 0; i < *nmemb; i++) {
		if (arr[i] == del)
			break;
	}
	if (i == *nmemb)
		return arr;
	for (; i < *nmemb-1; i++) {
		arr[i] = arr[i+1];
	}
	(*nmemb) --;
	arr = realloc(arr, *nmemb*sizeof(int));

	return arr;
}

void arr_traval(int *arr, int n)
{
	for (int i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}
	printf("\n");
}





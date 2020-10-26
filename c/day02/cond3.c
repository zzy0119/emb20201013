#include <stdio.h>

int main(void)
{
	int score;

	scanf("%d", &score);
	if (score < 0 || score > 100) {
		printf("成绩无效\n");
		return 1;
	}

	switch (score / 10) {
		case 10: // score == 100
		case 9:
			printf("A\n");	
			break; // 结束分支switch
		case 8:
			printf("B\n");
			break;
		case 7:
			printf("C\n");
			break;
		case 6:
			printf("D\n");
			break;
		case 5:
		case 4:
		case 3:
		case 2:
		case 1:
		case 0:
			printf("E\n");
			break;
		default:
			break;
	}
	


	return 0;
}


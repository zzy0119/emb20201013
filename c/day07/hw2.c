#include <stdio.h>

#define N	100

int main(void)
{
	char str[N] = {};
	int first, last;
	char t;
	int capitalCnt, lowercaseCnt, numberCnt;

	printf("请输入字符串:");
	scanf("%s", str);

	// 大写字母个数，小写字母个数，数字个数
	capitalCnt = lowercaseCnt = numberCnt = 0;
	for (int i = 0; str[i]; i++) {
		if (str[i] >= 'A' && str[i] <= 'Z') {
			capitalCnt ++;
			str[i] = str[i] + ('a'-'A');
		} else if (str[i] >= 'a' && str[i] <= 'z') {
			lowercaseCnt ++;
			str[i] -= ('a' - 'A');
		} else if (str[i] >= '0' && str[i] <= '9')
			numberCnt ++;
	}

	printf("大写个数:%d, 小写个数:%d, 数字字符:%d\n", \
			capitalCnt, lowercaseCnt, numberCnt);
	printf("%s\n", str);

	for (last = 0; str[last]; last++) {
		;	
	}
	last --;
	first = 0;
	while (first < last) {
		t = str[first];
		str[first] = str[last];
		str[last] = t;
		first ++;
		last --;
	}
	printf("%s\n", str);

	return 0;
}


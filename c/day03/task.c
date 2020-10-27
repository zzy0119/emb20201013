/*
 1. 要将5张100元的大钞票，换成等值的50元，20元，10元，5元一张的小钞票，每种面值至少1张，编程求需要多少张纸币。
 2. 用for编程找出100~200中的完全平方数
 3. 百钱百鸡”问题。百钱买百鸡，鸡翁一值钱三，鸡母一值钱二，鸡雏三值钱一，问鸡翁、鸡母、鸡雏各几何？
 */
#include <stdio.h>

int main(void)
{
	for (int five = 1; five < 10; five++) {
		for (int two = 1; two < 25; two ++) {
			for (int one = 1; one < 50; one ++) {
				for (int f = 1; f < 100; f++) {
					if (five*50+two*20+one*10+f*5 == 500) {
						printf("五十:%d,二十:%d,十元:%d,五元:%d, 共%d张\n", five, two, one, f, five+two+one+f);						
					}
				}
			}
		}
	}	

	// 完全平方数
	for (int i = 10; i * i <= 200 && i < 15; i++) {
		printf("%d 是完全平方数\n", i*i);	
	}

	// 公鸡的个数
	for (int i = 0; i <= 33; i++) {
		// 母鸡
		for (int j = 0; j <= 50; j++) {
			// 小鸡
			for (int z = 0; z <= 300; z+=3) {
				if (i + j + z == 100 && i*3+j*2+z/3==100)
					printf("公鸡:%d, 母鸡:%d, 小鸡:%d\n", \
							i, j, z);
			}
		}
	
	}

	return 0;
}


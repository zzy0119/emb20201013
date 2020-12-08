#include "tbf.h"


// 令牌桶
typedef struct {
	int cps;
	int token;
	int burst;
}tbf_t;

// 库
tbf_t *libs[MAXTBFS];


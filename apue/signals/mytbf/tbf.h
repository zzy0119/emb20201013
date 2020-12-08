#ifndef __TBF_H
#define __TBF_H

#define	MAXTBFS	1024

// 初始化令牌桶
int tbf_init(int cps, int burst);

// 取令牌
int tbf_fetchtoken(int tbfindex, int fetchtokens);

// 还令牌

// 销毁
void tbf_destory(int tbfindex);

#endif


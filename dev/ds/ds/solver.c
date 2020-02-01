#include "solver.h"
/**
 * @ 文件名: solver.h
 * @ 功能: 声明有关solver的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年2月1日
 *
 */

int InitialValue(pOPArray arr, int len, int* sArr, int sArrLen, double* output) {
	if (sArrLen <= 0 || len <= 0 || arr == NULL || sArr == NULL) {
		if (output != NULL)
			*output = 0;
		return 0;
	}
	int maxn = -1;
	for (int i = 0; i < len; ++i) {
		maxn = MAX(maxn, arr[i]);
	}
	if ((maxn + 1) / 2 - 1 > sArrLen)
		return 0;

	int dagger = -1, normal = -1;
	int nextIndex = -1;
	/* n表示creation operator的数目,即dagger的数目 */
	/* m表示anihilation operator的数目,即normal的数目 */
	int n = 0, m = 0;
	double ans = 1;
	int state = 0;
	while (state != -1) {
		switch (state) {
		case -1:
			/* 状态-1: 退出状态 */
			break;
		case 0:
			/* 状态0: 初始化 */
			nextIndex = 0;
			state = 1;
			break;
		case 1:
			/* 状态1: 更改dagger和normal */
			n = m = 0;
			normal = ((arr[nextIndex] + 1) / 2) * 2;
			dagger = normal - 1;
			state = 2;
			break;
		case 2:
			/* 状态2: 开始遍历同一块 */
			if (nextIndex >= len) {
				state = 3;
			}
			else if (arr[nextIndex] == normal) {
				++m;
				++nextIndex;
			}
			else if (arr[nextIndex] == dagger) {
				++n;
				++nextIndex;
			}
			else {
				state = 3;
			}
			break;
		case 3:
			/* 状态3: 统计n和m,更新ans */
		{
			if (n != m) {
				ans = 0;
				state = -1;
				break;
			}
			else {
				int n_alpha = sArr[normal / 2 - 1];
				if (n > n_alpha) {
					ans = 0;
					state = -1;
				}
				else {
					for (int i = n_alpha; i >= n_alpha - n + 1; --i) {
						ans *= i;
					}
				}

				if (nextIndex >= len)
					state = -1;
				else
					state = 1;
			}
			break;
		}
		default:
			break;
		}
	}

	*output = ans;

	return 1;
}

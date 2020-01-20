/**
 * @ 文件名: normalizer.c
 * @ 功能: 实现有关正交化的功能
 * @ 作者: AyajiLin & YesunHuang
 * @ 邮箱: 493987054@qq.com & 944812203@qq.com
 * @ github: https://github.com/leonardodalinky & https://github.com/yesunhuang
 * @ 日期: 2020年1月18日
 *
 */
#include "normalizer.h"

int MultiplyOfOPArray(pOPArray arr1, int len1, pOPArray arr2, int len2, pOPArray output, int* outLen) {
	if (len1 <= 0 || len2 <= 0 || arr1 == NULL || arr2 == NULL)
		return 0;
	int nowIndex1, nowIndex2;
	nowIndex1 = nowIndex2 = 0;
	int nextIndex1, nextIndex2;
	nextIndex1 = nextIndex2 = 0;
	int outputIndex = 0;
	_GetNextCPIndexFromOPArray(arr1, len1, nowIndex1, &nextIndex1);
	_GetNextCPIndexFromOPArray(arr2, len2, nowIndex2, &nextIndex2);
	while (nowIndex1 < len1 && nowIndex2 < len2) {
		int cp = 0;
		_CompareOPArrayBuffer(arr1 + nowIndex1, nextIndex1 - nowIndex1, arr2 + nowIndex2, nextIndex2 - nowIndex2, &cp);
		if (cp == 1) {
			/* buf1 > buf2 */
			for (; nowIndex2 < nextIndex2; ++nowIndex2) {
				output[outputIndex++] = arr2[nowIndex2];
			}
			_GetNextCPIndexFromOPArray(arr2, len2, nowIndex2, &nextIndex2);
		}
		else if (cp == 0) {
			/* buf1 == buf2 */
			for (; nowIndex1 < nextIndex1; ++nowIndex1) {
				output[outputIndex++] = arr1[nowIndex1];
			}
			_GetNextCPIndexFromOPArray(arr1, len1, nowIndex1, &nextIndex1);
			if (nowIndex1 == len1)
				output[outputIndex++] = 0;

			for (; nowIndex2 < nextIndex2; ++nowIndex2) {
				output[outputIndex++] = arr2[nowIndex2];
			}
			_GetNextCPIndexFromOPArray(arr2, len2, nowIndex2, &nextIndex2);
		}
		else {
			/* buf1 < buf2 */
			for (; nowIndex1 < nextIndex1; ++nowIndex1) {
				output[outputIndex++] = arr1[nowIndex1];
			}
			_GetNextCPIndexFromOPArray(arr1, len1, nowIndex1, &nextIndex1);
		}
	}

	/* 处理剩下的结点 */
	if (nowIndex1 == len1 && nowIndex2 == len2) {
		// do nothing
	}
	else if (nowIndex1 == len1) {
		output[outputIndex++] = 0;
		for (; nowIndex2 < len2; nowIndex2++) {
			output[outputIndex++] = arr2[nowIndex2];
		}
	}
	else {
		/* nowIndex2 == len2 */
		output[outputIndex++] = 0;
		for (; nowIndex1 < len1; nowIndex1++) {
			output[outputIndex++] = arr2[nowIndex1];
		}
	}

	if (outLen != NULL)
		*outLen = outputIndex;
	return 1;
}

void _CompareOPArrayBuffer(pOPArray arr1, int len1, pOPArray arr2, int len2, int* result) {
	if (len1 <= 0) {
		*result = -1;
		return;
	}
	else if (len2 <= 0) {
		*result = 1;
		return;
	}

	/* 预处理,排除末尾0的影响 */
	len1 = (arr1[len1 - 1] == 0) ? len1 - 1 : len1;
	len2 = (arr1[len2 - 1] == 0) ? len2 - 1 : len2;
	if (len1 <= 0) {
		*result = -1;
		return;
	}
	else if (len2 <= 0) {
		*result = 1;
		return;
	}

	/* 开始比较 */
	if (len1 < len2)
		*result = -1;
	else if (len1 > len2)
		*result = 1;
	else {
		/* len1 == len2 */
		*result = 0;
		for (int i = 0; i < len1; ++i) {
			if (arr1[i] > arr2[i]) {
				*result = 1;
				return;
			}
			else if (arr1[i] < arr2[i]) {
				*result = -1;
				return;
			}
		}
	}
	return;
}

int _GetNextCPIndexFromOPArray(pOPArray arr, int len, int now, int* next) {
	while (1) {
		if (now >= len) {
			*next = len;
			return 1;
		}
		else if (arr[now] == 0) {
			*next = now + 1;
			return 1;
		}
		else {
			now++;
		}
	}
}

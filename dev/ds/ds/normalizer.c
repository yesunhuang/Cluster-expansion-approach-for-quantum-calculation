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

int SONormalize(pOPArray arr, int len, int csize, pOPTree* outTree) {
	/* 默认输入符合格式 */
	if (len < 0) {
		*outTree = NULL;
		return 0;
	}
	else if (len == 0) {
		return CreateOPTree(0, outTree);
	}
	
	/* 做标记 */
	int normal = ((arr[0] + 1) / 2) * 2;
	int dagger = normal - 1;

	int* buf = (int*)malloc(sizeof(int) * ((len / 2) + 1));
	if (buf == NULL) return 0;
	int zeroNum = 0;
	memset(buf, 0, sizeof(int) * ((len / 2) + 1));
	buf[0] = 1;
	if (arr[len - 1] == dagger)
		zeroNum = 1;
	for (int i = len - 2; i >= 0; --i) {
		if (arr[i] == dagger) {
			++zeroNum;
		}
		else {
			/* arr[i] == normal */
			for (int j = zeroNum - 1; j >= 0; --j) {
				buf[j + 1] += buf[j] * (zeroNum - j);
			}
		}
	}
	
	/* 构造树 */
	CreateOPTree(csize, outTree);
	UINT_L* tempbuf = (UINT_L*)malloc(sizeof(UINT_L) * len);
	if (tempbuf == NULL) return 0;
	for (int i = 0; i < zeroNum; ++i) {
		tempbuf[i] = dagger;
	}
	for (int i = zeroNum; i < len; ++i) {
		tempbuf[i] = normal;
	}
	INT_V tempv = { buf[0], 0 };
	InsertOfOPTree(*outTree, tempbuf, len, tempv);
	for (int i = 1; i <= (len / 2); ++i) {
		// int arrlen = len - 2 * i;
		if (buf[i] != 0) {
			if (2 * i == len) {
				/* 0次项 */
				tempbuf[0] = 0;
				tempv.real = buf[i];
				InsertOfOPTree(*outTree, tempbuf, 1, tempv);
			}
			else {
				tempbuf[zeroNum - i] = normal;
				tempv.real = buf[i];
				InsertOfOPTree(*outTree, tempbuf, len - 2 * i, tempv);
			}
		}
	}
	
	free(tempbuf);
	free(buf);
	return 0;
}

int MONormalize(pOPArray arr, int len, pOPTree* outTree) {
	/* 默认输入符合格式,即无0 */
	if (len <= 0) {
		*outTree = NULL;
		return 0;
	}

	_SortMOArray(arr, len);
	int csize = -1;
	for (int i = 0; i < len; ++i) {
		csize = MAX(csize, arr[i]);
	}
	/* m为一个mode的系底 */
	int m = (arr[0] + 1) / 2;
	int start = 0, end = 0;
	/* 确定第一棵 */
	for (; end < len; ++end) {
		if (end == len - 1) {
			SONormalize(arr, len, csize, outTree);
			return 1;
		}
		else if ((arr[end + 1] != m * 2) && (arr[end + 1] != m * 2 - 1)) {
			SONormalize(arr, end + 1, csize, outTree);
			start = end = end + 1;
			m = (arr[start] + 1) / 2;
			break;
		}
	}
	/* 后续的乘树 */
	while (1) {
		if (end == len - 1) {
			pOPTree tempTree = NULL, tempAns = NULL;
			SONormalize(arr + start, end - start + 1, csize, &tempTree);
			MultiplyOfOPTree_TT(*outTree, tempTree, &tempAns);
			ExchangeOfOPTree(*outTree, tempAns);
			FreeOPTree(tempAns);
			FreeOPTree(tempTree);
			return 1;
		}
		else if ((arr[end + 1] != m * 2) && (arr[end + 1] != m * 2 - 1)) {
			pOPTree tempTree = NULL, tempAns = NULL;
			SONormalize(arr + start, end - start + 1, csize, &tempTree);
			MultiplyOfOPTree_TT(*outTree, tempTree, &tempAns);
			ExchangeOfOPTree(*outTree, tempAns);
			FreeOPTree(tempAns);
			FreeOPTree(tempTree);
			start = end = end + 1;
			m = (arr[start] + 1) / 2;
		}
		else {
			++end;
		}
	}

	return 1;
}

int MultiplyOfOPArray(pOPArray arr1, int len1, pOPArray arr2, int len2, pOPArray output, int* outLen) {
	if (len1 < 0 || len2 < 0 || arr1 == NULL || arr2 == NULL)
		return 0;
	else if (arr1[0] == 0) {
		memcpy(output, arr2, len2);
		if (outLen != NULL) *outLen = len2;
		return 1;
	}
	else if (arr2[0] == 0) {
		memcpy(output, arr1, len1);
		if (outLen != NULL) *outLen = len1;
		return 1;
	}
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
		if (outputIndex >= 1 && output[outputIndex - 1] != 0)
			output[outputIndex++] = 0;
		for (; nowIndex2 < len2; nowIndex2++) {
			output[outputIndex++] = arr2[nowIndex2];
		}
	}
	else {
		/* nowIndex2 == len2 */
		if (outputIndex >= 1 && output[outputIndex - 1] != 0)
			output[outputIndex++] = 0;
		for (; nowIndex1 < len1; nowIndex1++) {
			output[outputIndex++] = arr1[nowIndex1];
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
	len2 = (arr2[len2 - 1] == 0) ? len2 - 1 : len2;
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

int _SortMOArray(pOPArray arr, int len) {
	/* 冒泡排序,可stable */
	/* 默认输入妹有0,且符合格式 */
	if (arr == NULL || len <= 0)
		return 0;

	int lastChange = 0;
	int isChange = 1;
	while (lastChange < len - 1) {
		if (!isChange)
			return 1;
		isChange = 0;
		int tempLastChange = lastChange;
		for (int i = len - 1; i > lastChange; --i) {
			if (((arr[i] + 1) / 2) < ((arr[i - 1] + 1) / 2)) {
				isChange = 1;
				tempLastChange = i;
				SWAP(arr[i], arr[i - 1], UINT_L);
			}
		}
		lastChange = tempLastChange;
	}
	return 1;
}

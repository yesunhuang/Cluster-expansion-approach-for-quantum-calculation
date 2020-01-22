#include "simple_operator_hashmap.h"
/**
 * @ 文件名: so_hashmap.h
 * @ 功能: 实现单模式operator哈希表的功能
 * @ 作者: AyajiLin
 * @ 邮箱: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ 日期: 2020年1月20日
 *
 */

int InitSOLink(pSOHashLink link) {
	ClearSOLink(link);
	return 1;
}

int AddNodeOfSOLink(pSOHashLink link, int indexData) {
	if (link->head == NULL && link->tail == NULL) {
		link->head = link->tail = (pSOHashLinkNode)malloc(sizeof(SOHashLinkNode));
		if (link->head == NULL)
			return 0;
		link->head->index = indexData;
	}
	else{
		link->tail->next = (pSOHashLinkNode)malloc(sizeof(SOHashLinkNode));
		if (link->tail->next == NULL)
			return 0;
		link->tail = link->tail->next;
		link->tail->index = indexData;
		return 1;
	}
	return 0;
}

int ClearSOLink(pSOHashLink link) {
	if (link->head != NULL && link->tail != NULL) {
		pSOHashLinkNode nowNode = link->head;
		pSOHashLinkNode temp;
		while (nowNode != NULL) {
			temp = nowNode->next;
			free(nowNode);
			nowNode = temp;
		}
		link->head = link->tail = NULL;
	}
	return 1;
}

int MoveSOLink(pSOHashLink srcLink, pSOHashLink dstLink) {
	ClearSOLink(dstLink);
	dstLink->head = srcLink->head;
	dstLink->tail = srcLink->tail;
	srcLink->head = srcLink->tail = NULL;
	return 1;
}

int CreateSOHashmap(pSOHashmap * phm, int expectSize) {
	*phm = (pSOHashmap)malloc(sizeof(SOHashmap));
	_InitSOHashmap(*phm, expectSize);
	return 0;
}

int _InitSOHashmap(pSOHashmap hm, int expectSize) {
	int c = 0;
	_NearestLtEqPrime(expectSize * 10, &c);
	if (hm->data != NULL) free(hm->data);

	hm->data = (SimpleOperator*)malloc(c * sizeof(SimpleOperator));
	hm->capacity = c;
	hm->expect = expectSize;
	ClearSOHashmap(hm);
	return 1;
}

int ClearSOHashmap(pSOHashmap hm) {
	memset(hm->data, -1, hm->capacity * sizeof(SimpleOperator));
	ClearSOLink(&hm->hashLink);
	return 0;
}

int MoveSOHashmap(pSOHashmap srcHm, pSOHashmap dstHm) {
	if (dstHm->capacity != srcHm->capacity)
		return 0;
	ClearSOHashmap(dstHm);
	memcpy(dstHm->data, srcHm->data, srcHm->capacity * sizeof(SimpleOperator));
	MoveSOLink(&srcHm->hashLink, &dstHm->hashLink);
	return 1;
}

int InsertSOHashmap(pSOHashmap hm, SimpleOperator so) {
	int index = 0;
	_SOHashGen(so, hm->capacity, &index);
	int indexRecord = (index - 1 + hm->capacity) % hm->capacity;
	/* 线性探测法 */
	while (1) {
		if (hm->data[index].normal == -1) {
			hm->data[index] = so;
			AddNodeOfSOLink(&hm->hashLink, index);
			return 1;
		}
		else if (index == indexRecord) {
			return 0;
		}
		else {
			index = (index + 1) % hm->capacity;
		}
	}
}

int FreeSOHashmap(pSOHashmap hm) {
	ClearSOHashmap(hm);
	free(hm->data);
	free(hm);
	return 1;
}

int _NearestLtEqPrime(int num, int* output) {
	/* 用筛法找质数 */
	if (num == 1)
		return 0;
	else if (num == 2)
		return 1;

	int* buf = (int*)malloc((num + 1) * sizeof(int));
	if (buf == NULL) return 0;
	memset(buf, -1, (num + 1) * sizeof(int));
	buf[1] = buf[2] = 1;
	int nowNum = 2;
	/* 开始筛法 */
	while (nowNum <= num) {
		if (buf[nowNum] == 1) {
			int n = nowNum * 2;
			for (; n <= num; n += nowNum)
				buf[n] = 0;

			++nowNum;
		}
		else if (buf[nowNum] == -1) {
			buf[nowNum] = 1;
			continue;
		}
		else {
			/* buf[nowNum] == 0 */
			++nowNum;
		}
	}

	*output = 1;
	for (int i = num; i >= 1; --i) {
		if (buf[i] == 1) {
			*output = i;
			break;
		}
	}

	free(buf);
	return 1;
}

int _SOHashGen(SimpleOperator so, int capacity, int* output) {
	int normalDigits = 0;
	_GetDigits(so.dagger, &normalDigits);
	int m = 1;
	for (int i = 0; i < normalDigits; ++i)
		m *= 10;
	int t = (so.dagger * m + so.normal) % capacity;
	t = (t < 0) ? t + capacity : t;
	*output = t;
	return 1;
}

int _GetDigits(int num, int* output) {
	int ans = 0;
	while (num != 0) {
		num /= 10;
		++ans;
	}
	*output = ans;
	return 1;
}

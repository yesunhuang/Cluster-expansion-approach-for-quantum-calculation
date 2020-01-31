// Deprecated. Yesun nmsl.
/**
 * @ �ļ���: simple_operator_hashmap.h
 * @ ����: ������ģʽoperator��ϣ��Ĺ���
 * @ ����: AyajiLin
 * @ ����: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ ����: 2020��1��20��
 *
 */
#pragma once
#ifndef _SIMPLE_OPERATOR_HASHMAP_H_
#define _SIMPLE_OPERATOR_HASHMAP_H_

#include "simple_operator.h"
#include <malloc.h>
#include <memory.h>

#define NULL ((void*)0)

typedef struct _SOHashLinkNode {
	int index;
	struct _SOHashLinkNode* next;
} SOHashLinkNode, *pSOHashLinkNode;

typedef struct _SOHashLink {
	pSOHashLinkNode head;
	pSOHashLinkNode tail;
} SOHashLink, *pSOHashLink;

struct _SOHashmap {
	int capacity;
	int expect;
	SOHashLink hashLink;
	SimpleOperator* data;
};
typedef struct _SOHashmap SOHashmap, *pSOHashmap;

int InitSOLink(pSOHashLink link);
int AddNodeOfSOLink(pSOHashLink link, int indexData);
int ClearSOLink(pSOHashLink link);
int MoveSOLink(pSOHashLink srcLink, pSOHashLink dstLink);

int CreateSOHashmap(pSOHashmap * phm, int expectSize);
int _InitSOHashmap(pSOHashmap hm, int expectSize);
int ClearSOHashmap(pSOHashmap hm);
int MoveSOHashmap(pSOHashmap srcHm, pSOHashmap dstHm);
int InsertSOHashmap(pSOHashmap hm, SimpleOperator so);
int FreeSOHashmap(pSOHashmap hm);

int _NearestLtEqPrime(int num, int* output);
int _SOHashGen(SimpleOperator so, int capacity, int* output);
int _GetDigits(int num, int* output);


#endif // !_SIMPLE_OPERATOR_HASHMAP_H_

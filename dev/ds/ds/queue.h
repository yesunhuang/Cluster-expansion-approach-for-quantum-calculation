/**
 * @ �ļ���: queue.h
 * @ ����: ����queue�Ĺ���
 * @ ����: AyajiLin
 * @ ����: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ ����: 2020��1��19��
 *
 */
#pragma once
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <malloc.h>

/* ֻ�洢void*���͵Ķ��� */
typedef struct _Queue {
	// ���׵�Ԫ��λ��
	int headIndex;
	// ��β�ĺ�һ��Ԫ�ص�λ��
	int tailIndex;
	// ����Ԫ�ص��������
	int capacity;
	// ����Ԫ�ص�ʵ������
	int size;
	// ���������Ŀռ�
	void** buffer;
} *Queue;

/* CreateQueue��FreeQueue����ʹ�� */
int CreateQueue(const int capacity, Queue* output);
int InitQueue(Queue q, const int capacity);
int PushQueue(Queue q, const void* input);
int PopQueue(Queue q, void** output);
int GetQueueHead(Queue q, void** output);
int GetQueueTail(Queue q, void** output);
int GetQueueSize(Queue q, int* output);
int IsEmptyQueue(Queue q);
int ClearQueue(Queue q);
/* CreateQueue��FreeQueue����ʹ�� */
int FreeQueue(Queue q);

#endif // !_QUEUE_H_
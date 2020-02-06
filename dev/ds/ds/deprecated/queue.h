/**
 * @ 文件名: queue.h
 * @ 功能: 声明queue的功能
 * @ 作者: AyajiLin
 * @ 邮箱: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ 日期: 2020年1月19日
 *
 */
#pragma once
#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <malloc.h>

/* 只存储void*类型的队列 */
typedef struct _Queue {
	// 队首的元素位置
	int headIndex;
	// 队尾的后一个元素的位置
	int tailIndex;
	// 队列元素的最多数量
	int capacity;
	// 队列元素的实际数量
	int size;
	// 队列所开的空间
	void** buffer;
} *Queue;

/* CreateQueue和FreeQueue搭配使用 */
int CreateQueue(const int capacity, Queue* output);
int InitQueue(Queue q, const int capacity);
int PushQueue(Queue q, const void* input);
int PopQueue(Queue q, void** output);
int GetQueueHead(Queue q, void** output);
int GetQueueTail(Queue q, void** output);
int GetQueueSize(Queue q, int* output);
int IsEmptyQueue(Queue q);
int ClearQueue(Queue q);
/* CreateQueue和FreeQueue搭配使用 */
int FreeQueue(Queue q);

#endif // !_QUEUE_H_
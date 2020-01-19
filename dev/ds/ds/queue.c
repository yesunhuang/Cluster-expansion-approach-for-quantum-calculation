/**
 * @ 文件名: queue.c
 * @ 功能: 实现queue的功能
 * @ 作者: AyajiLin
 * @ 邮箱: 493987054@qq.com
 * @ github: https://github.com/leonardodalinky
 * @ 日期: 2020年1月19日
 *
 */
#include "queue.h"

int CreateQueue(const int capacity, Queue* output) {
	*output = (Queue*)malloc(sizeof(Queue));
	if (*output == NULL) 
		return 0;
	InitQueue(*output, capacity);
	return 1;
}

int InitQueue(Queue q, const int capacity) {
	q->headIndex = 0;
	q->tailIndex = -1;
	q->size = 0;
	q->capacity = capacity;
	if (q->buffer != NULL)
		free(q->buffer);
	q->buffer = (void**)malloc(sizeof(void*) * capacity);
	if (q->buffer == NULL) {
		q->capacity = 0;
		return 0;
	}
	return 1;
}

int PushQueue(Queue q, const void* input) {
	if (q->size == q->capacity)
		return 0;

	q->tailIndex = (q->tailIndex == q->capacity - 1) ? 0 : q->tailIndex + 1;
	q->buffer[q->tailIndex] = input;
	++q->size;
	return 1;
}

int PopQueue(Queue q, void** output) {
	if (q->size == 0)
		return 0;

	*output = q->buffer[q->headIndex];
	q->headIndex = (q->headIndex == q->capacity - 1) ? 0 : q->headIndex + 1;
	--q->size;
	return 1;
}

int GetQueueHead(Queue q, void** output) {
	if (q->size == 0)
		return 0;

	*output = q->buffer[q->headIndex];
	return 1;
}

int GetQueueTail(Queue q, void** output) {
	if (q->size == 0)
		return 0;

	*output = q->buffer[q->tailIndex];
	return 1;
}

int GetQueueSize(Queue q, int* output) {
	*output = q->size;
	return 1;
}

int IsEmptyQueue(Queue q) {
	return (q->size == 0) ? 1 : 0;
}

int ClearQueue(Queue q) {
	return InitQueue(q, q->capacity);
}

int FreeQueue(Queue q) {
	free(q->buffer);
	free(q);
	return 1;
}

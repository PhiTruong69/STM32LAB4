/*
 * queue.h
 *
 *  Created on: Nov 9, 2025
 *      Author: PHITRUONGPC
 */

#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_
#include <stdint.h>
#include <stdlib.h>
#include <limits.h>

typedef struct QueueNode QueueNode_t;

typedef struct QueueNode{
	uint8_t task_id;
	QueueNode_t* next_node;
}QueueNode_t;

typedef struct {
	QueueNode_t* head;
	QueueNode_t* tail;

	uint8_t size;
}Queue;

void Queue_Init(Queue* queue);

void Queue_PushBack(uint8_t task_id, Queue* queue);
uint8_t Queue_PopFront(Queue* queue);
#endif /* INC_QUEUE_H_ */

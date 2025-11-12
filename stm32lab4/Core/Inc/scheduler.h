/*
 * scheduler.h
 *
 *  Created on: Nov 9, 2025
 *      Author: PHITRUONGPC
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>
#include <stdlib.h>
#include "queue.h"

#include "main.h"
#define SCH_MAX_TASKS     40
#define TICK              10
typedef struct TaskNode TaskNode_t;

typedef struct {
	void (* task_function)(void);

	int32_t delay;
	int32_t period;

	uint8_t task_id;
}Task;

typedef struct TaskNode{
	Task* task;
	TaskNode_t* next_node;
}TaskNode_t;

void SCH_Init();

uint8_t SCH_AddTask(void (* function)(void), int32_t delay, int32_t period);
void SCH_DeleteTask(uint8_t task_id);
void SCH_Update();
void SCH_Dispatch_Tasks();

void add(TaskNode_t* head_node, TaskNode_t* new_node);
TaskNode_t* pop(TaskNode_t* head_node);
#endif /* INC_SCHEDULER_H_ */

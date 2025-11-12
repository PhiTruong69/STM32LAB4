/*
 * scheduler.c
 *
 *  Created on: Nov 9, 2025
 *      Author: PHITRUONGPC
 */


#include "scheduler.h"
Queue avalable_task_id_list; //ID task còn trống
Queue ready_task_list;       // ID task sẳn sàng

Task task_list[SCH_MAX_TASKS] = {};
TaskNode_t* head;

void SCH_Init(){

	Queue_Init(&avalable_task_id_list);
	Queue_Init(&ready_task_list);

	// dummy node
	head = (TaskNode_t*)malloc(sizeof(TaskNode_t));
	head->next_node = 0;

	//Initialize task_id that are "free"
	for(int i = 0; i < SCH_MAX_TASKS; ++i){
		Queue_PushBack(i, &avalable_task_id_list);
	}
}
void SCH_Update(){
	if(head->next_node == 0){  // không có task, return
		return;
	}

	if(head->next_node && head->next_node->task->delay <= 0){  // có task và delay <= 0
		TaskNode_t* timed_up_task = pop(head);
		if(timed_up_task == 0){
			return;
		}

		uint8_t removed_task_id = timed_up_task->task->task_id;
		Queue_PushBack(removed_task_id, &ready_task_list); // dua id vao ready

		if(timed_up_task->task->period > 0){ //lap lai
			timed_up_task->task->delay = timed_up_task->task->period;
			add(head, timed_up_task);
		}
		else{
			free(timed_up_task);
		}

	}

	if(head->next_node){
		head->next_node->task->delay -= 1; //giam delay
	}
}
uint8_t SCH_AddTask(void (* function)(void), int32_t delay, int32_t period){
	uint8_t task_id = Queue_PopFront(&avalable_task_id_list); //lay 1 id trong

	task_list[task_id].task_id = task_id;
	task_list[task_id].task_function = function;
	task_list[task_id].delay = delay / TICK;
	task_list[task_id].period = period / TICK;

	TaskNode_t* new_node = (TaskNode_t*)malloc(sizeof(TaskNode_t));
	new_node->task = &task_list[task_id];
	new_node->next_node = 0;

	add(head, new_node); //tao node moi va them vao list
	return task_id;
}

void SCH_DeleteTask(uint8_t task_id){
	task_list[task_id].task_id = 0;
	task_list[task_id].task_function = 0;
	task_list[task_id].delay = 0;
	task_list[task_id].period = 0;
}



void SCH_Dispatch_Tasks(){
	if(ready_task_list.size > 0){
		uint8_t finished_task_id = Queue_PopFront(&ready_task_list);
		if(task_list[finished_task_id].task_function != 0){
			(*task_list[finished_task_id].task_function)(); // thuc hien
		}

		if(task_list[finished_task_id].period <= 0){
			SCH_DeleteTask(finished_task_id);  // 1 short
			Queue_PushBack(finished_task_id, &avalable_task_id_list);

		}
	}
}

void add(TaskNode_t* head_node, TaskNode_t* new_node){
	TaskNode_t* current_node = head_node;
 // neu delay cua node hien tai < delay cua node moi
	while(current_node->next_node && current_node->next_node->task->delay < new_node->task->delay){
		new_node->task->delay -= current_node->next_node->task->delay;
		current_node = current_node->next_node;
	}

	new_node->next_node = current_node->next_node;
	current_node->next_node = new_node;

	if(new_node->next_node != 0){
		new_node->next_node->task->delay -= new_node->task->delay;
	}
}

TaskNode_t* pop(TaskNode_t* head_node){ //lay node dau ra khoi danh sach
	if(head_node->next_node == 0){
		return 0;
	}

	TaskNode_t* removed_node = head_node->next_node;
	head_node->next_node = removed_node->next_node;
	return removed_node;
}

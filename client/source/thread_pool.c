/*************************************************************************
	> File Name: thread_pool.c
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Tue 07 May 2024 07:34:00 PM CST
	> Describe: 
 ************************************************************************/

#include "../include/head.h"
#include "../include/thread_pool.h"

void task_queue_init(struct task_queue *taskQueue, int size) {
    taskQueue->size = size;
	taskQueue->total = taskQueue->head = taskQueue->tail = 0;
	taskQueue->data = calloc(size, sizeof(void *));
	pthread_mutex_init(&taskQueue->mutex, NULL);
	pthread_cond_init(&taskQueue->cond, NULL);
	return ;
}

void task_queue_push(struct task_queue *taskQueue, void *data) {
	pthread_mutex_lock(&taskQueue->mutex);
	if (taskQueue->total == taskQueue->size) {
		pthread_mutex_unlock(&taskQueue->mutex);
		return ;
	}
	taskQueue->data[taskQueue->tail] = data;
	taskQueue->total++;
	taskQueue->tail++;
	if (taskQueue->tail == taskQueue->size) {
		taskQueue->tail = 0;
	}
	pthread_cond_signal(&taskQueue->cond);
	pthread_mutex_unlock(&taskQueue->mutex);
	return ;
}

void *task_queue_pop(struct task_queue *taskQueue) {
    pthread_mutex_lock(&taskQueue->mutex);
	while (taskQueue->total == 0) {
		pthread_cond_wait(&taskQueue->cond, &taskQueue->mutex);
	}
	void *data = taskQueue->data[taskQueue->head];
	taskQueue->total--;
	if (++taskQueue->head == taskQueue->size) {
		taskQueue->head = 0;
	}
	pthread_mutex_unlock(&taskQueue->mutex);
	return data;
}

void *thread_run(void *arg) {
    pthread_detach(pthread_self());
	struct task_queue *taskQueue = (struct task_queue *)arg;
	while(1) {
		void *data = task_queue_pop(taskQueue);
		// doing...
	}
}

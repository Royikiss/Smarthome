/*************************************************************************
	> File Name: thread_pool.h
	> Author:Royi 
	> Mail:royi990001@gmail.com 
	> Created Time: Tue 07 May 2024 07:22:40 PM CST
	> Describe: 
 ************************************************************************/
#ifndef _THREAD_POOL_H__
#define _THREAD_POOL_H__

#include <pthread.h>

struct task_queue {
    int head, tail, size, total;
    void **data;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

void task_queue_init(struct task_queue *taskQueue, int size);

void task_queue_push(struct task_queue *taskQueue, void *data);

void *task_queue_pop(struct task_queue *taskQueue);

void *thread_run(void *arg);

#endif


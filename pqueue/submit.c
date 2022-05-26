
#include <stdlib.h>

#include <semaphore.h>

#include <debug.h>

#include <task/compare.h>

#include "struct.h"
#include "submit.h"

int pqueue_submit(struct pqueue* this, struct task* task)
{
	int error = 0;
	ENTER;
	
	sem_wait(this->array_lock);
	
	if (this->n + 1 >= this->cap)
	{
		this->cap = this->cap * 2 ?: 1;
		this->tasks = realloc(this->tasks, sizeof(*this->tasks) * this->cap);
	}
	
	if (!error)
	{
		size_t i;
		struct task** const tasks = this->tasks, *swap;
		
		tasks[this->n] = task;
		
		for (i = this->n; i > 0 && compare_tasks(tasks[i / 2], tasks[i]); i >>= 1)
		{
			swap = tasks[i];
			tasks[i] = tasks[i / 2];
			tasks[i / 2] = swap;
		}
		
		this->n++;
	}
	
	sem_post(this->array_lock);
	
	sem_post(this->counter);
	
	EXIT;
	return error;
}














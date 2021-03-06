
#include <assert.h>
#include <stddef.h>

#include <debug.h>

#include <task/struct.h>
#include <task/compare.h>

#include "struct.h"
#include "pop.h"

struct task* pqueue_pop(struct pqueue* this)
{
	ENTER;
	
	sem_wait(this->counter);
	
	sem_wait(this->array_lock);
	
	assert (this->n);
	
	struct task* retval = this->tasks[0], *swap;
	
	if (retval->kind == tk_shutdown)
	{
		sem_post(this->counter);
	}
	else if (--this->n)
	{
		int l, r, smallest, i = 0;
		struct task** tasks = this->tasks;
		
		tasks[0] = tasks[this->n];
		
		again: l = 2 * i + 1, r = l + 1, smallest = i;
		
		if (l < this->n && compare_tasks(tasks[l], tasks[i]) < 0)
			smallest = l;
		
		if (r < this->n && compare_tasks(tasks[r], tasks[smallest]) < 0)
			smallest = r;
		
		if (smallest != i)
		{
			swap = tasks[i];
			tasks[i] = tasks[smallest];
			tasks[smallest] = swap;
			
			i = smallest;
			
			goto again;
		}
	}
	
	sem_post(this->array_lock);
	
	EXIT;
	return retval;
}
















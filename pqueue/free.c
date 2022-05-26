
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include <task/free.h>

#include "struct.h"
#include "free.h"

void free_pqueue(struct pqueue* this)
{
	size_t i, n;
	ENTER;
	
	for (i = 0, n = this->n; i < n; i++)
		free_task(this->tasks[i]);
	
	free(this->tasks);
	
	sem_destroy(this->array_lock);
	sem_destroy(this->counter);
	
	free(this->array_lock);
	free(this->counter);
	free(this);
	
	EXIT;
}


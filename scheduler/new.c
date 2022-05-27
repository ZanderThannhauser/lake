
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <misc/ssem_init.h>

#include "node/compare.h"
#include "node/free.h"
#include "struct.h"
#include "new.h"

int new_scheduler(struct scheduler** out, struct pqueue* pqueue)
{
	int error = 0;
	sem_t* lock = NULL;
	ENTER;
	
	struct scheduler* this = NULL;
	
	error = 0
		?: ssem_init(&lock, 0, 1)
		?: smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		this->pqueue = pqueue;
		this->lock = lock, lock = NULL;
		
		avl_init_tree(&this->tree, compare_scheduler_node, free_scheduler_node);
		
		*out = this;
	}
	
	if (lock)
	{
		sem_destroy(lock);
		free(lock);
	}
	
	EXIT;
	return error;
}























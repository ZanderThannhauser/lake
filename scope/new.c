
#include <stdlib.h>

#include <avl/avl.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <misc/ssem_init.h>

#include "variable/compare.h"
#include "variable/free.h"

#include "struct.h"
#include "new.h"

int new_scope(struct scope** out)
{
	int error = 0;
	sem_t* lock = NULL;
	struct scope* this;
	ENTER;
	
	error = 0
		?: ssem_init(&lock, 0, 1)
		?: smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		avl_init_tree(&this->tree, compare_variable, free_variable);
		this->lock = lock, lock = NULL;
		
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











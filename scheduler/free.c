
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_scheduler(struct scheduler* this)
{
	ENTER;
	
	avl_free_nodes(&this->tree);
	
	sem_destroy(this->lock);
	
	free(this->lock);
	free(this);
	
	EXIT;
}


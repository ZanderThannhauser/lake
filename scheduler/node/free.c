
#include <stdlib.h>

#include <debug.h>

#include "link/free.h"
#include "struct.h"
#include "free.h"

void free_scheduler_node(void* a)
{
	struct scheduler_node* this = a;
	ENTER;
	
	if (this)
	{
		free(this->name);
		
		free_scheduler_node_link(this->waiting);
		
		free(this);
	}
	
	EXIT;
}


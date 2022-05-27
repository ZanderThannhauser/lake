
#include <stdlib.h>

#include <debug.h>

#include "../../bundle/free.h"

#include "struct.h"
#include "free.h"

void free_scheduler_node_link(struct scheduler_node_link* this)
{
	ENTER;
	
	if (this)
	{
		free_scheduler_bundle(this->bundle);
		free_scheduler_node_link(this->next);
		free(this);
	}
	
	EXIT;
}


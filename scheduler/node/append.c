
#include <stdio.h>

#include <debug.h>

#include "../bundle/struct.h"

#include "link/struct.h"
#include "link/new.h"

#include "struct.h"
#include "append.h"

int scheduler_node_append(
	struct scheduler_node* this,
	struct scheduler_bundle* bundle)
{
	int error = 0;
	ENTER;
	
	struct scheduler_node_link* link = NULL;
	
	error = new_scheduler_node_link(&link, bundle);
	
	if (!error)
	{
		link->next = this->waiting;
		this->waiting = link;
		
		bundle->unresolved++;
	}
	
	EXIT;
	return error;
}


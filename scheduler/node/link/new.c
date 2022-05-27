
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

int new_scheduler_node_link(
	struct scheduler_node_link** out,
	struct scheduler_bundle* bundle)
{
	int error = 0;
	ENTER;
	
	struct scheduler_node_link* this;
	
	error = smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		this->bundle = bundle;
		this->next = NULL;
		
		*out = this;
	}
	
	EXIT;
	return error;
}


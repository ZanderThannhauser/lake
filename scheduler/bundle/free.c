
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_scheduler_bundle(struct scheduler_bundle* this)
{
	ENTER;
	
	if (this && !this->unresolved)
	{
		free(this);
	}
	
	EXIT;
}


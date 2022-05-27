
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

int new_scheduler_bundle(
	struct scheduler_bundle** out,
	struct task* task)
{
	int error = 0;
	ENTER;
	
	struct scheduler_bundle* this;
	
	error = smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		this->unresolved = 0;
		this->task = task;
		
		*out = this;
	}
	
	EXIT;
	return error;
}



#include <debug.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

int new_shutdown_task(struct task** out)
{
	int error = 0;
	ENTER;
	
	struct shutdown_task* this;
	
	error = new_task(
		/* this: */ (struct task**) &this,
		/* kind: */ tk_shutdown,
		/* inheritance: */ &shutdown_task_inheritance,
		/* alloc_size: */ sizeof(*this));
	
	if (!error)
	{
		*out = (struct task*) this;
	}
	
	EXIT;
	return error;
}


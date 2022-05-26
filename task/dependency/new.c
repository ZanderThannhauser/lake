
#include <debug.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

int new_dependency_task(
	struct task** out,
	char* name,
	struct expression* expression)
{
	int error = 0;
	ENTER;
	
	struct dependency_task* this;
	
	error = new_task(
		/* this: */ (struct task**) &this,
		/* kind: */ tk_dependency,
		/* inheritance: */ &dependency_task_inheritance,
		/* alloc_size: */ sizeof(*this));
	
	if (!error)
	{
		this->name = name;
		this->expression = expression;
		
		*out = (struct task*) this;
	}
	
	EXIT;
	return error;
}


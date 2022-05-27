
#include <stdlib.h>

#include <debug.h>

#include <memory/sstrdup.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

int new_evaluate_task(
	struct task** out,
	char* name,
	struct expression* expression)
{
	int error = 0;
	char* dup = NULL;
	ENTER;
	
	struct evaluate_task* this;
	
	error = 0
		?: sstrdup(&dup, name)
		?: new_task(
		/* this: */ (struct task**) &this,
		/* kind: */ tk_evaluate,
		/* inheritance: */ &evaluate_task_inheritance,
		/* alloc_size: */ sizeof(*this));
	
	if (!error)
	{
		this->name = dup, dup = NULL;
		this->expression = expression;
		
		*out = (struct task*) this;
	}
	
	free(dup);
	
	EXIT;
	return error;
}


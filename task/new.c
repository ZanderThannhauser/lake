
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

int new_task(
	struct task** out,
	enum task_kind kind,
	struct task_inheritance* inheritance,
	size_t alloc_size)
{
	int error = 0;
	ENTER;
	
	struct task* this = NULL;
	
	error = smalloc((void**) &this, alloc_size);
	
	if (!error)
	{
		this->kind = kind;
		this->inheritance = inheritance;
		
		*out = this;
	}
	
	EXIT;
	return error;
}


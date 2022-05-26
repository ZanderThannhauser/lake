
#include <stdlib.h>

#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_dependency_task(struct task* super)
{
	struct dependency_task* const this = (struct dependency_task*) super;
	ENTER;
	
	free(this->name);
	free_expresssion(this->expression);
	
	EXIT;
}


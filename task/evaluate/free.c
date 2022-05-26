
#include <stdlib.h>

#include <debug.h>

#include <expression/free.h>

#include "struct.h"
#include "free.h"

void free_evaluate_task(struct task* super)
{
	struct evaluate_task* const this = (struct evaluate_task*) super;
	ENTER;
	
	free(this->name);
	free_expresssion(this->expression);
	
	EXIT;
}


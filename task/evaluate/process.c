
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <macros/strequals.h>

#include <task/shutdown/new.h>
#include <task/free.h>

#include <pqueue/submit.h>

#include "struct.h"
#include "process.h"

int evaluate_task_process(struct task* super, struct pqueue* pqueue)
{
	int error = 0;
	struct evaluate_task* const this = (struct evaluate_task*) super;
	ENTER;
	
	// do the actual evaluation
	TODO;
	
	if (strequals(this->name, "printme"))
	{
		struct task* shutdown = NULL;
		
		error = new_shutdown_task(&shutdown);
		
		if (!error)
			error = pqueue_submit(pqueue, shutdown);
		
		if (error)
			free_task(shutdown);
	}
	
	EXIT;
	return error;
}













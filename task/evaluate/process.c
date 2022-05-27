
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <macros/strequals.h>

#include <task/shutdown/new.h>
#include <task/free.h>

#include <pqueue/submit.h>

#include <expression/evaluate.h>

#include <scope/declare.h>

#include <scheduler/release.h>

#include "struct.h"
#include "process.h"

int evaluate_task_process(
	struct task* super,
	struct pqueue* pqueue,
	struct scheduler* scheduler,
	struct scope* scope)
{
	int error = 0;
	struct evaluate_task* const this = (struct evaluate_task*) super;
	ENTER;
	
	// do the actual evaluation
	double value = expression_evaluate(this->expression, scope);
	
	dpv(value);
	
	error = 0
		?: scope_declare(scope, this->name, value)
		?: scheduler_release(scheduler, this->name);
	
	if (!error && strequals(this->name, "main"))
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














#include <stddef.h>

#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <misc/strset/new.h>
#include <misc/strset/free.h>

#include <expression/get_references.h>

#include <task/evaluate/new.h>
#include <task/free.h>

#include <pqueue/submit.h>

#include <scheduler/schedule.h>

#include "struct.h"
#include "process.h"

int dependency_task_process(
	struct task* super,
	struct pqueue* pqueue,
	struct scheduler* scheduler,
	struct scope* scope)
{
	int error = 0;
	struct task* evaluate = NULL;
	struct strset* references = NULL;
	struct dependency_task* const this = (struct dependency_task*) super;
	ENTER;
	
	error = 0
		?: new_strset(&references)
		?: expression_get_references(this->expression, references)
		?: new_evaluate_task(&evaluate, this->name, this->expression)
		?: scheduler_schedule(scheduler, references, evaluate);
	
	if (error)
		free_task(evaluate);
	else
		this->expression = NULL;
	
	free_strset(references);
	
	EXIT;
	return error;
}













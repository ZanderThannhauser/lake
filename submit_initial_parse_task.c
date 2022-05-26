
#include <stddef.h>

#include <debug.h>

#include <task/parse/new.h>
#include <task/free.h>

#include <pqueue/submit.h>

#include "submit_initial_parse_task.h"

int submit_initial_parse_task(
	struct pqueue* pqueue,
	const char* input_path)
{
	int error = 0;
	ENTER;
	
	struct task* task = NULL;
	
	error = 0
		?: new_parse_task(&task, input_path)
		?: pqueue_submit(pqueue, task);
	
	if (error)
		free_task(task);
	
	EXIT;
	return error;
}


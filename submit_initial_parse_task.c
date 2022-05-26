
#include <stdlib.h>
#include <stddef.h>

#include <debug.h>

#include <memory/sstrdup.h>

#include <task/parse/new.h>
#include <task/free.h>

#include <pqueue/submit.h>

#include "submit_initial_parse_task.h"

int submit_initial_parse_task(
	struct pqueue* pqueue,
	const char* input_path)
{
	int error = 0;
	char* dup = NULL;
	ENTER;
	
	struct task* task = NULL;
	
	error = sstrdup(&dup, input_path);
	
	if (!error)
		error = new_parse_task(&task, dup);
	
	if (error)
		free(dup);
	
	if (!error)
		error = pqueue_submit(pqueue, task);
	
	if (error)
		free_task(task);
	
	EXIT;
	return error;
}













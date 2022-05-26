
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

/*#include <task/shutdown/new.h>*/
/*#include <task/free.h>*/

#include <pqueue/submit.h>

#include "struct.h"
#include "process.h"

int dependency_task_process(struct task* super, struct pqueue* pqueue)
{
	int error = 0;
	struct dependency_task* const this = (struct dependency_task*) super;
	ENTER;
	
	TODO;
	
	EXIT;
	return error;
}













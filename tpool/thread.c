
#include <stdio.h>
#include <assert.h>
#include <debug.h>

#include <defines/CSI.h>

#include <pqueue/pop.h>

#include <task/process.h>
#include <task/print.h>

#include "threadargs.h"
#include "thread.h"

void* thread(void* x)
{
	struct task* task;
	struct threadargs* args = x;
	ENTER;
	
	struct pqueue* const pqueue = args->pqueue;
	const unsigned id = args->id;
	const bool verbose = args->verbose;
	
	while ((task = pqueue_pop(args->pqueue)))
	{
		// write task line
		if (verbose) task_print(task, args->id);
		
		int error = task_process(task, pqueue);
		
		// if there was an error: shutdown.
		if (error)
		{
			TODO;
		}
		
		// clear task line
		#ifdef RELEASE
		if (verbose)
		{
			// Move cursor down the indicated # of rows, to column 1.
			printf(CSI "%u" "E", id);
			
			// erase whole line.
			printf(CSI "2" "K");
			
			// Move cursor up the indicated # of rows, to column 1.
			printf(CSI "%u" "F", id);
		}
		#endif
	}
	
	EXIT;
	return NULL;
}
















#include <unistd.h>
#include <stdio.h>
#include <assert.h>
#include <debug.h>

#include <defines/CSI.h>

#include <pqueue/pop.h>

#include <task/struct.h>
#include <task/process.h>
#include <task/print.h>
#include <task/free.h>

#include "threadargs.h"
#include "thread.h"

void* thread(void* x)
{
	struct task* task;
	struct threadargs* args = x;
	ENTER;
	
	struct pqueue* const pqueue = args->pqueue;
	
	struct scheduler* const scheduler = args->scheduler;
	
	struct scope* const scope = args->scope;
	
	const unsigned id = args->id;
	
	const bool verbose = args->verbose;
	
	sem_t* const print_lock = args->print_lock;
	
	while ((task = pqueue_pop(args->pqueue))->kind != tk_shutdown)
	{
		// write task line
		if (verbose)
		{
			sem_wait(print_lock);
			task_print(task, id);
			sem_post(print_lock);
			
			#ifdef RELEASE
/*			usleep(     100 * 1000);*/
			usleep(     300 * 1000);
/*			usleep(     500 * 1000);*/
/*			usleep(1 * 1000 * 1000);*/
			#endif
		}
		
		int error = task_process(task, pqueue, scheduler, scope);
		
		// if there was an error: shutdown.
		if (error)
		{
			TODO;
		}
		
		// clear task line
		#ifdef RELEASE
		if (verbose)
		{
			sem_wait(print_lock);
			
			// Move cursor up the indicated # of rows, to column 1.
			printf(CSI "%u" "F", id);
			
			// erase whole line.
			printf(CSI "2" "K");
/*			printf(" -- erased -- ");*/
			
			// Move cursor down the indicated # of rows, to column 1.
			printf(CSI "%u" "E", id);
			
			sem_post(print_lock);
			
			fflush(stdout);
		}
		#endif
		
		free_task(task);
	}
	
	EXIT;
	return NULL;
}
















#include <stdio.h>
#include <stdlib.h>

#include <assert.h>

#include <pthread.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <defines/CSI.h>

#include <misc/ssem_init.h>

#include "struct.h"
#include "threadargs.h"
#include "thread.h"
#include "new.h"

int new_tpool(
	struct tpool** out,
	struct pqueue* pqueue,
	struct scheduler* scheduler,
	struct scope* scope,
	bool verbose,
	unsigned number_of_threads)
{
	size_t i;
	int error = 0;
	struct threadargs* threadargs = NULL;
	pthread_t* threads = NULL;
	sem_t* print_lock = NULL;
	ENTER;
	
	error = 0
		?: ssem_init(&print_lock, 0, 1)
		?: smalloc((void**) &threadargs, sizeof(*threadargs) * number_of_threads)
		?: smalloc((void**) &threads, sizeof(*threads) * number_of_threads);
	
	for (i = 0; !error && i < number_of_threads; i++)
	{
		struct threadargs* args = &threadargs[i];
		
		args->pqueue = pqueue;
		args->scheduler = scheduler;
		args->scope = scope;
		args->id = i + 1;
		args->verbose = verbose;
		args->print_lock = print_lock;
		
		if (pthread_create(&threads[i], NULL, thread, args))
		{
			TODO;
			error = 1;
		}
	}
	
	struct tpool* this = NULL;
	
	if (!error)
		error = smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		this->threadargs = threadargs, threadargs = NULL;
		this->threads = threads, threads = NULL;
		
		this->number_of_threads = number_of_threads;
		
		this->print_lock = print_lock, print_lock = NULL;
		
		this->has_joined = false;
		
		// clear task line
		#ifdef RELEASE
		if (verbose)
		{
			// Move cursor down the indicated # of rows, to column 1.
			for (i = 0; i < number_of_threads; i++) putchar('\n');
			fflush(stdout);
		}
		#endif
		
		*out = this;
	}
	
	if (threads)
	{
		TODO; // while(i) pthread_kill(threads[i--]);
		
		free(threads);
	}
	
	if (print_lock)
		sem_destroy(print_lock);
	
	free(threadargs);
	
	EXIT;
	return error;
}

















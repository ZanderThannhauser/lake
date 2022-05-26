
#include <stdlib.h>

#include <assert.h>

#include <pthread.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "threadargs.h"
#include "thread.h"
#include "new.h"

int new_tpool(
	struct tpool** out,
	struct pqueue* pqueue,
	bool verbose,
	unsigned number_of_threads)
{
	size_t i;
	int error = 0;
	struct threadargs* threadargs = NULL;
	pthread_t* threads = NULL;
	ENTER;
	
	error = 0
		?: smalloc((void**) &threadargs, sizeof(*threadargs) * number_of_threads)
		?: smalloc((void**) &threads, sizeof(*threads) * number_of_threads);
	
	for (i = 0; !error && i < number_of_threads; i++)
	{
		struct threadargs* args = &threadargs[i];
		
		args->pqueue = pqueue;
		args->id = i;
		args->verbose = verbose;
		
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
		
		*out = this;
	}
	
	if (threads)
	{
		TODO; // while(i) pthread_kill(threads[i--]);
		
		free(threads);
	}
	
	free(threadargs);
	
	EXIT;
	return error;
}

















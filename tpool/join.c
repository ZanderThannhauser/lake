
#include <pthread.h>
#include <debug.h>

#include "struct.h"
#include "join.h"

int tpool_join(struct tpool* this)
{
	int error = 0;
	size_t i, n;
	ENTER;
	
	for (i = 0, n = this->number_of_threads; i < n; i++)
		pthread_join(this->threads[i], NULL);
	
	this->has_joined = true;
	
	EXIT;
	return error;
}


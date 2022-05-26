
#include <enums/error.h>

#include <debug.h>

#include <memory/smalloc.h>

#include <misc/ssem_init.h>

#include "struct.h"
#include "new.h"

int new_pqueue(struct pqueue** out)
{
	int error = 0;
	sem_t *array_lock = NULL, *counter = NULL;
	ENTER;
	
	struct pqueue* new = NULL;
	
	error = 0
		?: ssem_init(&array_lock, 0, 1)
		?: ssem_init(&counter, 0, 0)
		?: smalloc((void**) &new, sizeof(*new));
	
	if (!error)
	{
		new->tasks = NULL;
		new->n = 0, new->cap = 0;
		
		new->array_lock = array_lock, array_lock = NULL;
		new->counter = counter, counter = NULL;
		
		*out = new;
	}
	
	if (array_lock)
		sem_destroy(array_lock);
	
	if (counter)
		sem_destroy(counter);
	
	EXIT;
	return error;
}














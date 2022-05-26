
#include <enums/error.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

int new_pqueue(struct pqueue** out)
{
	int error = 0;
	sem_t array_lock, counter;
	ENTER;
	
	if (sem_init(&array_lock, 0, 1) < 0)
		error = e_syscall_failed;
	else if (sem_init(&counter, 0, 0) < 0)
		error = e_syscall_failed;
	
	struct pqueue* new = NULL;
	
	error = smalloc((void**) &new, sizeof(*new));
	
	if (!error)
	{
		new->tasks = NULL;
		new->n = 0, new->cap = 0;
		
		new->array_lock = array_lock;
		new->counter = counter;
		
		*out = new;
	}
	
	EXIT;
	return error;
}














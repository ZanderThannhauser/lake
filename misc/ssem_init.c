
#include <stdio.h>
#include <stdlib.h>

#include <debug.h>

#include <enums/error.h>

#include <defines/argv0.h>

#include <memory/smalloc.h>

#include "ssem_init.h"

int ssem_init(sem_t** out, int pshared, unsigned value)
{
	int error = 0;
	sem_t* new = NULL;
	ENTER;
	
	error = smalloc((void**) &new, sizeof(*new));
	
	if (!error && sem_init(new, pshared, value) < 0)
		fprintf(stderr, "%s: sem_init(): %m\n", argv0),
		error = e_syscall_failed;
	
	if (error)
		free(new);
	else
		*out = new;
	
	EXIT;
	return error;
}


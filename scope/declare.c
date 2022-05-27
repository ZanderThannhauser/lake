
#include <assert.h>
#include <stddef.h>

#include <enums/error.h>

#include <debug.h>

#include "variable/new.h"
#include "variable/free.h"

#include "struct.h"
#include "declare.h"

int scope_declare(
	struct scope* this,
	char* name, double value)
{
	int error = 0;
	struct variable* var = NULL;
	ENTER;
	
	error = new_variable(&var, name, value);
	
	if (!error)
	{
		sem_wait(this->lock);
		
		if (!avl_insert(&this->tree, var))
		{
			TODO;
			error = e_out_of_memory;
		}
		
		sem_post(this->lock);
	}
	
	if (error)
		free_variable(var);
	
	EXIT;
	return error;
}


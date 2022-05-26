
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_variable_expression(struct expression* super)
{
	struct variable_expression* const this = (struct variable_expression*) super;
	ENTER;
	
	free(this->name);
	
	EXIT;
}


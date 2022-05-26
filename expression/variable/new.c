
#include <debug.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

int new_variable_expression(struct expression** new, char* name)
{
	int error = 0;
	ENTER;
	
	struct variable_expression* this;
	
	error = new_expression(
		/* out: */ (struct expression**) &this,
		/* kind: */ ek_variable,
		/* inheritance: */ &variable_expression_inheritance,
		/* alloc_size: */ sizeof(*this));
	
	if (!error)
	{
		this->name = name;
		
		*new = (struct expression*) this;
	}
	
	EXIT;
	return error;
}


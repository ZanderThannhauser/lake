
#include <debug.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

int new_literal_expression(struct expression** out, double value)
{
	int error = 0;
	ENTER;
	
	struct literal_expression* this;
	
	error = new_expression(
		/* out: */ (struct expression**) &this,
		/* kind: */ ek_literal,
		/* inheritance: */ &literal_expression_inheritance,
		/* alloc_size: */ sizeof(*this));
	
	if (!error)
	{
		this->value = value;
		
		*out = (struct expression*) this;
	}
	
	EXIT;
	return error;
}


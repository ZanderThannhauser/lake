
#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

int new_expression(
	struct expression** out,
	enum expression_kind kind,
	struct expression_inheritance* inheritance,
	size_t alloc_size)
{
	int error = 0;
	ENTER;
	
	struct expression* this;
	
	error = smalloc((void**) &this, alloc_size);
	
	if (!error)
	{
		this->kind = kind;
		this->inheritance = inheritance;
		
		*out = this;
	}
	
	EXIT;
	return error;
}


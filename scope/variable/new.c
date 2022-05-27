
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>
#include <memory/sstrdup.h>

#include "struct.h"
#include "new.h"

int new_variable(
	struct variable** out,
	const char* name,
	double value)
{
	int error = 0;
	char* dup = NULL;
	ENTER;
	
	struct variable* this;
	
	error = 0
		?: sstrdup(&dup, name)
		?: smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		this->name = dup, dup = NULL;
		this->value = value;
		
		*out = this;
	}
	
	free(dup);
	
	EXIT;
	return error;
}


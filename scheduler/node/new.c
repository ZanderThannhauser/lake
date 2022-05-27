
#include <stdlib.h>

#include <debug.h>

#include <memory/smalloc.h>
#include <memory/sstrdup.h>

#include "struct.h"
#include "new.h"

int new_scheduler_node(
	struct scheduler_node** out,
	const char* name)
{
	int error = 0;
	char* dup = NULL;
	ENTER;
	
	struct scheduler_node* this;
	
	error = 0
		?: sstrdup(&dup, name)
		?: smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		this->name = dup, dup = NULL;
		this->has_flushed = false;
		this->waiting = NULL;
		
		dpvs(this->name);
		
		*out = this;
	}
	
	free(dup);
	
	EXIT;
	return error;
}


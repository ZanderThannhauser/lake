
#include <stdlib.h>

#include <string.h>

#include <debug.h>

#include <memory/smalloc.h>

#include "struct.h"
#include "new.h"

int new_strset(struct strset** out)
{
	int error = 0;
	ENTER;
	
	struct strset* this = NULL;
	
	error = smalloc((void**) &this, sizeof(*this));
	
	if (!error)
	{
		avl_init_tree(&this->tree, (void*) strcmp, free);
		
		*out = this;
	}
	
	EXIT;
	return error;
}


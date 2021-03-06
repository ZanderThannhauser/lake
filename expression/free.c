
#include <stdlib.h>

#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "free.h"

void free_expresssion(struct expression* this)
{
	ENTER;
	
	if (this)
	{
		assert(this->inheritance->free);
		
		(this->inheritance->free)(this);
		
		free(this);
	}
	
	EXIT;
}


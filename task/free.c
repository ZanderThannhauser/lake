
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "free.h"

void free_task(struct task* this)
{
	ENTER;
	
	assert(this->inheritance->free);
	
	(this->inheritance->free)(this);
	
	free(this);
	
	EXIT;
}


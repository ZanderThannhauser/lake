
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "get_references.h"

int expression_get_references(struct expression* this, struct strset* set)
{
	int error = 0;
	ENTER;
	
	dpv(this->kind);
	
	assert((this->inheritance->get_references));
	
	error = (this->inheritance->get_references)(this, set);
	
	EXIT;
	return error;
}


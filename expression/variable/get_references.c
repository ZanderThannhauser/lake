
#include <debug.h>

#include <misc/strset/add.h>

#include "struct.h"
#include "get_references.h"

int variable_expression_get_references(struct expression* super, struct strset* set)
{
	int error = 0;
	struct variable_expression* const this = (struct variable_expression*) super;
	ENTER;
	
	error = strset_add(set, this->name);
	
	EXIT;
	return error;
}


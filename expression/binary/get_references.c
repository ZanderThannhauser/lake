
#include <debug.h>

#include "../get_references.h"

#include "struct.h"
#include "get_references.h"

int binary_expression_get_references(
	struct expression* super,
	struct strset* references)
{
	int error = 0;
	struct binary_expression* const this = (void*) super;
	ENTER;
	
	error = 0
		?: expression_get_references(this->left, references)
		?: expression_get_references(this->right, references);
	
	EXIT;
	return error;
}


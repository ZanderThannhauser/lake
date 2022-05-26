
#include <debug.h>

#include "../new.h"

#include "inheritance.h"
#include "struct.h"
#include "new.h"

int new_binary_expression(
	struct expression** out,
	enum binary_expression_kind kind,
	struct expression* left,
	struct expression* right)
{
	int error = 0;
	ENTER;
	
	struct binary_expression* this;
	
	error = new_expression(
		/* out: */ (struct expression**) &this,
		/* kind: */ ek_binary,
		/* inheritance: */ &binary_expression_inheritance,
		/* alloc_size: */ sizeof(*this));
	
	if (!error)
	{
		this->kind = kind;
		this->left = left;
		this->right = right;
		
		*out = (struct expression*) this;
	}
	
	EXIT;
	return error;
}


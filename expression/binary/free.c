
#include <debug.h>

#include "../free.h"

#include "struct.h"
#include "free.h"

void free_binary_expression(struct expression* super)
{
	struct binary_expression* const this = (struct binary_expression*) super;
	ENTER;
	
	free_expresssion(this->left);
	free_expresssion(this->right);
	
	EXIT;
}


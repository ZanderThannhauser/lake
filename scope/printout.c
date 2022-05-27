
#include <stdio.h>

#include <debug.h>

#include "variable/struct.h"
#include "struct.h"
#include "printout.h"

int scope_printout(struct scope* this)
{
	int error = 0;
	struct avl_node_t* node;
	struct variable* var;
	ENTER;
	
	for (node = this->tree.head; node; node = node->next)
	{
		var = node->item;
		printf("%10s: %5lg\n", var->name, var->value);
	}
	
	EXIT;
	return error;
}


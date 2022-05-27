
#include <debug.h>

#include "struct.h"
#include "foreach.h"

int strset_foreach(struct strset* this, int (*callback)(char*))
{
	int error = 0;
	struct avl_node_t* node;
	ENTER;
	
	for (node = this->tree.head; !error && node; node = node->next)
		error = callback(node->item);
	
	EXIT;
	return error;
}


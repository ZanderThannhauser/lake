
#include <stdlib.h>

#include <debug.h>

#include <avl/avl.h>

#include "struct.h"
#include "free.h"

void free_strset(struct strset* this)
{
	ENTER;
	
	avl_free_nodes(&this->tree);
	
	free(this);
	
	EXIT;
}



#include <assert.h>

#include <debug.h>

#include "variable/struct.h"

#include "struct.h"
#include "lookup.h"

double scope_lookup(struct scope* this, const char* name)
{
	double retval;
	ENTER;
	
	dpvs(name);
	
	sem_wait(this->lock);
	
	struct avl_node_t* node = avl_search(&this->tree, &name);
	
	assert(node);
	
	struct variable* var = node->item;
	
	retval = var->value;
	
	sem_post(this->lock);
	
	EXIT;
	return retval;
}


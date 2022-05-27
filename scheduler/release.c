
#include <stddef.h>
#include <assert.h>

#include <enums/error.h>

#include <debug.h>

#include <pqueue/submit.h>

#include "bundle/struct.h"
#include "bundle/free.h"

#include "node/struct.h"
#include "node/new.h"
#include "node/link/struct.h"
#include "node/link/free.h"
#include "node/free.h"

#include "struct.h"
#include "release.h"

int scheduler_release(
	struct scheduler* this,
	const char* name)
{
	int error = 0;
	struct avl_node_t* _node;
	ENTER;
	
	dpvs(name);
	
	sem_wait(this->lock);
	
	if ((_node = avl_search(&this->tree, &name)))
	{
		struct scheduler_node* node = _node->item;
		
		assert(!node->has_flushed);
		
		struct scheduler_node_link* link;
		struct scheduler_bundle* bundle;
		
		for (link = node->waiting; !error && link; link = link->next)
		{
			dpv(link->bundle->unresolved);
			
			if (!--(bundle = link->bundle)->unresolved)
			{
				error = pqueue_submit(this->pqueue, bundle->task);
			}
		}
		
		free_scheduler_node_link(node->waiting), node->waiting = NULL;
		
		node->has_flushed = true;
	}
	else
	{
		struct scheduler_node* node = NULL;
		
		error = new_scheduler_node(&node, name);
		
		if (!error)
		{
			node->has_flushed = true;
			
			if (avl_insert(&this->tree, node))
			{
				node = NULL;
			}
			else
			{
				TODO;
				error = e_out_of_memory;
			}
		}
		
		free_scheduler_node(node);
	}
	
	sem_post(this->lock);
	
	EXIT;
	return error;
}














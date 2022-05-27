

#include <stdio.h>
#include <stddef.h>
#include <assert.h>

#include <enums/error.h>

#include <defines/argv0.h>

#include <debug.h>

#include <misc/strset/new.h>
/*#include <misc/strset/is_empty.h>*/
#include <misc/strset/foreach.h>
#include <misc/strset/free.h>

#include <pqueue/submit.h>

#include "bundle/struct.h"
#include "bundle/new.h"
#include "bundle/free.h"

#include "node/struct.h"
#include "node/new.h"
#include "node/append.h"
#include "node/free.h"

#include "struct.h"
#include "schedule.h"

int scheduler_schedule(
	struct scheduler* this,
	struct strset* references,
	struct task* task)
{
	int error = 0;
	struct scheduler_bundle* bundle = NULL;
	ENTER;
	
	sem_wait(this->lock);
	
	error = 0
		?: new_scheduler_bundle(&bundle, task)
		?: strset_foreach(references, ({
			int callback(char* reference)
			{
				int error = 0;
				struct avl_node_t* _node;
				ENTER;
				
				dpvs(reference);
				
				if ((_node = avl_search(&this->tree, &reference)))
				{
					struct scheduler_node* const node = _node->item;
					
					if (!node->has_flushed)
					{
						// add this bundle to node
						// unresolved++;
						TODO;
					}
				}
				else
				{
					struct scheduler_node* node = NULL;
					
					error = 0
						?: new_scheduler_node(&node, reference)
						?: scheduler_node_append(node, bundle);
					
					if (!error && !avl_insert(&this->tree, node))
						fprintf(stderr, "%s: avl_insert(): %m\n", argv0),
						error = e_out_of_memory;
					
					if (error)
						free_scheduler_node(node);
				}
				
				EXIT;
				return error;
			}
			callback;
		}));
	
	if (!error)
	{
		if (bundle->unresolved)
			bundle = NULL;
		else
			error = pqueue_submit(this->pqueue, task);
	}
	
	sem_post(this->lock);
	
	free_scheduler_bundle(bundle);
	
	EXIT;
	return error;
}













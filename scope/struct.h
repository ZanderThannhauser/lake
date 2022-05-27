
#include <semaphore.h>

#include <avl/avl.h>

struct scope
{
	struct avl_tree_t tree;
	
	sem_t* lock;
};


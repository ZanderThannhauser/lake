
#include <semaphore.h>
#include <avl/avl.h>

struct scheduler
{
	struct pqueue* pqueue;
	
	struct avl_tree_t tree;
	
	sem_t* lock;
};


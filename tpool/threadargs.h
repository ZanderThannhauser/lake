
#include <semaphore.h>

#include <stdbool.h>

struct threadargs
{
	struct pqueue* pqueue;
	struct scheduler* scheduler;
	struct scope* scope;
	
	unsigned id;
	
	bool verbose;
	
	sem_t* print_lock;
};


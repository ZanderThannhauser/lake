
#include <semaphore.h>

#include <stdbool.h>

struct threadargs
{
	struct pqueue* pqueue;
	unsigned id;
	bool verbose;
	sem_t* print_lock;
};


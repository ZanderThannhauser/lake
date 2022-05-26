
#include <semaphore.h>

struct task;

struct pqueue
{
	struct task** tasks;
	size_t n, cap;
	
	sem_t array_lock, counter;
};


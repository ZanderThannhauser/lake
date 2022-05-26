
#include <stdbool.h>
#include <semaphore.h>

struct tpool
{
	struct threadargs* threadargs;
	pthread_t* threads;
	
	size_t number_of_threads;
	
	sem_t* print_lock;
	
	bool has_joined;
};


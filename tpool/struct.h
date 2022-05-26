
struct tpool
{
	struct threadargs* threadargs;
	pthread_t* threads;
	size_t number_of_threads;
};


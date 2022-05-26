
struct tpool;
struct pqueue;

int new_tpool(
	struct tpool** out,
	struct pqueue* pqueue,
	bool verbose,
	unsigned number_of_threads);

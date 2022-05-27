
struct scope;
struct tpool;
struct pqueue;

int new_tpool(
	struct tpool** out,
	struct pqueue* pqueue,
	struct scheduler* scheduler,
	struct scope* scope,
	bool verbose,
	unsigned number_of_threads);

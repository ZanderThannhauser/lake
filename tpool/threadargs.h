
#include <stdbool.h>

struct threadargs
{
	struct pqueue* pqueue;
	unsigned id;
	bool verbose;
};


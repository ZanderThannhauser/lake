
struct dgraph_link
{
	char* name; // must be the first
	
	unsigned count;
	
	struct task* task;
	
	struct dgraph_link* next;
};


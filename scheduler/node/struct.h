
#include <stdbool.h>

struct scheduler_node_link;

struct scheduler_node
{
	char* name; // must be the first
	
	bool has_flushed;
	
	struct scheduler_node_link* waiting;
};



struct scheduler_bundle;
struct scheduler_node_link;

struct scheduler_node_link
{
	struct scheduler_bundle* bundle;
	struct scheduler_node_link* next;
};


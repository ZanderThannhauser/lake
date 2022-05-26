
#include "../struct.h"

struct shutdown_task
{
	struct task super;
	char* name;
	struct expression* expression;
};


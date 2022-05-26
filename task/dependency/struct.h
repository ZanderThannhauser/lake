
#include "../struct.h"

struct dependency_task
{
	struct task super;
	char* name;
	struct expression* expression;
};


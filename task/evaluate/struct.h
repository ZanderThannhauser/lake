
#include "../struct.h"

struct evaluate_task
{
	struct task super;
	char* name;
	struct expression* expression;
};


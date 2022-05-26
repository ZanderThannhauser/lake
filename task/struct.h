
#include "kind.h"

struct task
{
	enum task_kind kind;
	
	struct task_inheritance* inheritance;
};


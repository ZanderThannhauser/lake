
#include "../inheritance.h"

#include "free.h"

struct task_inheritance shutdown_task_inheritance = {
	.free = free_shutdown_task,
};

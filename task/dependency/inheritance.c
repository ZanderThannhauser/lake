
#include "../inheritance.h"

#include "compare.h"
#include "process.h"
#include "print.h"
#include "free.h"

struct task_inheritance dependency_task_inheritance = {
	.compare = compare_dependency_task,
	.process = dependency_task_process,
	.print = dependency_task_print,
	.free = free_dependency_task,
};

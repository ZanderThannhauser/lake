
#include "../inheritance.h"

#include "process.h"
#include "print.h"

struct task_inheritance dependency_task_inheritance = {
	.process = dependency_task_process,
	.print = dependency_task_print,
};

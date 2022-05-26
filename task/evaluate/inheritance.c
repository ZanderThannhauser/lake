
#include "../inheritance.h"

#include "process.h"
#include "print.h"
#include "free.h"

struct task_inheritance evaluate_task_inheritance = {
	.process = evaluate_task_process,
	.print = evaluate_task_print,
	.free = free_evaluate_task,
};

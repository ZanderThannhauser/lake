
#include "../inheritance.h"

#include "compare.h"
#include "process.h"
#include "print.h"
#include "free.h"

struct task_inheritance parse_task_inheritance = {
	.compare = compare_parse_task,
	.process = parse_task_process,
	.print = parse_task_print,
	.free = free_parse_task,
};

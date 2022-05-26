
#include <stddef.h>

#include "kind.h"

struct task;
struct task_inheritance;

int new_task(
	struct task** out,
	enum task_kind kind,
	struct task_inheritance* inheritance,
	size_t alloc_size);

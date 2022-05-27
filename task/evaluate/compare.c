
#include <string.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_evaluate_task(
	const struct task* super_a,
	const struct task* super_b)
{
	int cmp = 0;
	const struct evaluate_task* const a = (struct evaluate_task*) super_a;
	const struct evaluate_task* const b = (struct evaluate_task*) super_b;
	ENTER;
	
	dpvs(a->name);
	dpvs(b->name);
	
	cmp = strverscmp(a->name, b->name);
	
	EXIT;
	return cmp;
}



#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_dependency_task(
	const struct task* super_a,
	const struct task* super_b)
{
	int cmp = 0;
	const struct dependency_task* const a = (struct dependency_task*) super_a;
	const struct dependency_task* const b = (struct dependency_task*) super_b;
	ENTER;
	
	dpvs(a->name);
	dpvs(b->name);
	
	cmp = strverscmp(a->name, b->name);
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}


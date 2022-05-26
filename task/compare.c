
#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "compare.h"

int compare_tasks(const struct task* a, const struct task* b)
{
	int cmp = 0;
	ENTER;
	
	cmp = a->kind - b->kind;
	
	if (!cmp && a->inheritance->compare)
		cmp = (a->inheritance->compare)(a, b);
	
	EXIT;
	return cmp;
}



#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_scheduler_node(const void* a, const void* b)
{
	int cmp = 0;
	const struct scheduler_node* A = a, *B = b;
	ENTER;
	
	cmp = strcmp(A->name, B->name);
	
	EXIT;
	return cmp;
}


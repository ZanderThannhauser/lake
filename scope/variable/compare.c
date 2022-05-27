
#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_variable(const void* a, const void* b)
{
	int cmp = 0;
	const struct variable* A = a, *B = b;
	ENTER;
	
	cmp = strcmp(A->name, B->name);
	
	EXIT;
	return cmp;
}



#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_variable(void* ptr)
{
	struct variable* this = ptr;
	ENTER;
	
	free(this->name);
	free(this);
	
	EXIT;
}


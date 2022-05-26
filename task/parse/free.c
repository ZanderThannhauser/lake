
#include <stdlib.h>

#include <debug.h>

#include "struct.h"
#include "free.h"

void free_parse_task(struct task* super)
{
	struct parse_task* const this = (struct parse_task*) super;
	ENTER;
	
	free(this->input_path);
	
	EXIT;
}


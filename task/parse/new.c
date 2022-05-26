
#include <debug.h>

#include "../new.h"

#include "struct.h"
#include "inheritance.h"
#include "new.h"

int new_parse_task(
	struct task** out,
	char* input_path)
{
	int error = 0;
	ENTER;
	
	struct parse_task* this;
	
	error = new_task((struct task**) &this, tk_parse, &parse_task_inheritance, sizeof(*this));
	
	if (!error)
	{
		this->input_path = input_path;
		
		*out = (struct task*) this;
	}
	
	EXIT;
	return error;
}


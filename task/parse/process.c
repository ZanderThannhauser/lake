
#include <debug.h>

#include <enums/error.h>

#include "parse/parse.h"

#include "struct.h"
#include "process.h"

int parse_task_process(struct task* super, struct pqueue* pqueue)
{
	int error = 0;
	struct parse_task* const this = (struct parse_task*) super;
	ENTER;
	
	error = parse(this->input_path, pqueue);
	
	EXIT;
	return error;
}













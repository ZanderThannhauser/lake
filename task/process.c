
#include <assert.h>

#include <debug.h>

#include "inheritance.h"
#include "struct.h"
#include "process.h"

int task_process(struct task* this, struct pqueue* pqueue)
{
	int error = 0;
	
	assert(this->inheritance->process);
	
	error = (this->inheritance->process)(this, pqueue);
	
	return error;
}


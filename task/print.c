
#include <assert.h>
#include <stdio.h>
#include <debug.h>

#include <defines/CSI.h>

#include "inheritance.h"
#include "struct.h"
#include "print.h"

void task_print(struct task* this, unsigned row)
{
	ENTER;
	
	// Move cursor down the indicated # of rows, to column 1.
	#ifdef RELEASE
	printf(CSI "%u" "E", row);
	#endif
	
	assert(this->inheritance->print);
	
	(this->inheritance->print)(this);
	
	// Move cursor up the indicated # of rows, to column 1.
	#ifdef RELEASE
	printf(CSI "%u" "F", row);
	#endif
	
	fflush(stdout);
	
	EXIT;
}


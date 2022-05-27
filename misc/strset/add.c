
#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <stdio.h>
#include <avl/avl.h>

#include <enums/error.h>

#include <debug.h>

#include <memory/sstrdup.h>

#include "struct.h"
#include "add.h"

int strset_add(struct strset* this, char* str)
{
	int error = 0;
	char* dup = NULL;
	ENTER;
	
	dpvs(str);
	
	error = sstrdup(&dup, str);
		
	if (avl_insert(&this->tree, dup))
	{
		ddprintf("brand new\n");
		dup = NULL;
	}
	else if (errno != EEXIST)
	{
		TODO;
		error = e_out_of_memory;
	}
	
	free(dup);
	
	EXIT;
	return error;
}



















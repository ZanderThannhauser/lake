
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "join.h"
#include "free.h"

void free_tpool(struct tpool* this)
{
	ENTER;
	
	if (!this->has_joined)
		tpool_join(this);
	
	sem_destroy(this->print_lock);
	free(this->print_lock);
	
	free(this->threads);
	free(this->threadargs);
	free(this);
	
	EXIT;
}


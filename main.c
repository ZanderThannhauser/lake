
#include <assert.h>

#include <debug.h>
#include <stdio.h>

#include <cmdln/struct.h>
#include <cmdln/process.h>
#include <cmdln/free.h>

#include <pqueue/new.h>
#include <pqueue/free.h>

#include <scheduler/new.h>
#include <scheduler/free.h>

#include <tpool/new.h>
#include <tpool/join.h>
#include <tpool/free.h>

#include <scope/new.h>
#include <scope/printout.h>
#include <scope/free.h>

#include "submit_initial_parse_task.h"

int main(int argc, char* argv[])
{
	int error = 0;
	struct cmdln* flags = NULL;
	struct scope* scope = NULL;
	struct scheduler* scheduler = NULL;
	struct pqueue* pqueue = NULL;
	struct tpool* tpool = NULL;
	ENTER;
	
	error = 0
		?: cmdln_process(&flags, argc, argv)
		?: new_scope(&scope)
		?: new_pqueue(&pqueue)
		?: new_scheduler(&scheduler, pqueue)
		?: new_tpool(&tpool, pqueue, scheduler, scope,
			flags->verbose, flags->number_of_threads)
		?: submit_initial_parse_task(pqueue, flags->input_path)
		?: tpool_join(tpool)
		?: scope_printout(scope);
	
	free_scope(scope);
	free_scheduler(scheduler);
	free_pqueue(pqueue);
	free_tpool(tpool);
	free_cmdln(flags);
	
	EXIT;
	return error;
}















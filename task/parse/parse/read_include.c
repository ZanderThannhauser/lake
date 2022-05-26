
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <memory/sstrdup.h>

#include <task/parse/new.h>
#include <task/free.h>

#include <pqueue/submit.h>

#include "tokenize/scanner.h"
#include "tokenize/read_token.h"

#include "read_include.h"

int read_include(struct scanner* scanner, struct pqueue* pqueue)
{
	int error = 0;
	ENTER;
	
	assert(scanner->token == t_include);
	
	error = read_token(scanner);
	
	if (!error && scanner->token != t_string_literal)
	{
		TODO;
		error = 1;
	}
	
	char* path = NULL;
	
	if (!error)
		error = sstrdup(&path, scanner->tokenchars.chars);
	
	if (!error)
		error = read_token(scanner);
	
	struct task* task = NULL;
	
	if (!error)
		error = new_parse_task(&task, path);
	
	if (error)
		free(path);
	
	if (!error)
		error = pqueue_submit(pqueue, task);
	
	if (error)
		free_task(task);
	
	EXIT;
	return error;
}














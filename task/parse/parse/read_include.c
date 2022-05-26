
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include <debug.h>

#include <enums/error.h>

#include <defines/argv0.h>

#include <memory/sstrdup.h>

#include <task/parse/new.h>
#include <task/free.h>

#include <pqueue/submit.h>

#include "tokenize/scanner.h"
#include "tokenize/read_token.h"

#include "read_include.h"

int read_include(struct scanner* scanner, const char* dirpath, struct pqueue* pqueue)
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
	
	char* whole_path = NULL;
	
	if (!error && asprintf(&whole_path, "%s/%s", dirpath, path) < 0)
		fprintf(stderr, "%s: asprintf(): %m\n", argv0),
		error = e_out_of_memory;
	
	free(path);
	
	struct task* task = NULL;
	
	if (!error)
		error = new_parse_task(&task, whole_path);
	
	if (error)
		free(whole_path);
	
	if (!error)
		error = pqueue_submit(pqueue, task);
	
	if (error)
		free_task(task);
	
	EXIT;
	return error;
}














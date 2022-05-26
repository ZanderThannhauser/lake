
#include <stdlib.h>
#include <assert.h>
#include <debug.h>

#include <memory/sstrdup.h>

#include <expression/free.h>

#include <task/dependency/new.h>
#include <task/free.h>

#include <pqueue/submit.h>

#include "tokenize/scanner.h"
#include "tokenize/read_token.h"

#include "read_expression.h"
#include "read_let.h"

int read_let(struct scanner* scanner, struct pqueue* pqueue)
{
	int error = 0;
	ENTER;
	
	assert(scanner->token == t_let);
	
	error = read_token(scanner);
	
	if (!error && scanner->token != t_identifier)
	{
		TODO;
		error = 1;
	}
	
	char* variable_name = NULL;
	
	if (!error)
		error = sstrdup(&variable_name, scanner->tokenchars.chars);
	
	if (!error)
		error = read_token(scanner);
	
	if (!error && scanner->token != t_equals)
	{
		TODO;
		error = 1;
	}
	
	if (!error)
		error = read_token(scanner);
	
	struct expression* expression = NULL;
	
	if (!error)
		error = read_expression(&expression, scanner);
	
	if (!error && scanner->token != t_semicolon)
	{
		TODO;
		error = 1;
	}
	
	if (!error)
		error = read_token(scanner);
	
	struct task* task = NULL;
	
	if (!error)
		error = new_dependency_task(&task, variable_name, expression);
	
	if (error)
		free(variable_name),
		free_expresssion(expression);
	
	if (!error)
		error = pqueue_submit(pqueue, task);
	
	if (error)
		free_task(task);
	
	EXIT;
	return error;
}














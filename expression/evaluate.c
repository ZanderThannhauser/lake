
#include <assert.h>

#include <debug.h>

#include "struct.h"
#include "inheritance.h"
#include "evaluate.h"

double expression_evaluate(
	struct expression* this,
	struct scope* scope)
{
	double answer;
	ENTER;
	
	assert(this->inheritance->evaluate);
	
	answer = (this->inheritance->evaluate)(this, scope);
	
	EXIT;
	return answer;
}


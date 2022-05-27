
#include <debug.h>

#include <scope/lookup.h>

#include "struct.h"
#include "evaluate.h"

double variable_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	double answer;
	struct variable_expression* const this = (struct variable_expression*) super;
	ENTER;
	
	answer = scope_lookup(scope, this->name);
	
	dpv(answer);
	
	EXIT;
	return answer;
}


#include <debug.h>

#include "struct.h"
#include "evaluate.h"

double literal_expression_evaluate(
	struct expression* super,
	struct scope* _)
{
	double answer;
	struct literal_expression* const this = (struct literal_expression*) super;
	ENTER;
	
	dpv(this->value);
	
	answer = this->value;
	
	EXIT;
	return answer;
}

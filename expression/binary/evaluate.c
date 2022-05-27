
#include <assert.h>

#include <math.h>

#include <debug.h>

#include "../evaluate.h"

#include "struct.h"
#include "evaluate.h"

double binary_expression_evaluate(
	struct expression* super,
	struct scope* scope)
{
	double answer, left, right;
	struct binary_expression* const this = (struct binary_expression*) super;
	ENTER;
	
	left = expression_evaluate(this->left, scope);
	right = expression_evaluate(this->right, scope);
	
	switch (this->kind)
	{
		case bek_add: answer = left + right; break;
		case bek_subtract: answer = left - right; break;
		case bek_multiply: answer = left * right; break;
		case bek_divide: answer = left / right; break;
		case bek_remainder: TODO; break;
		case bek_exponential: answer = pow(left, right); break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return answer;
}

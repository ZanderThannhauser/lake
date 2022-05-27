
#include "evaluate.h"
#include "get_references.h"
#include "inheritance.h"
#include "free.h"

struct expression_inheritance variable_expression_inheritance = {
	.get_references = variable_expression_get_references,
	.evaluate = variable_expression_evaluate,
	.free = free_variable_expression,
};


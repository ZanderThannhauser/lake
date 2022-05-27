
#include "evaluate.h"
#include "get_references.h"
#include "inheritance.h"
#include "free.h"

struct expression_inheritance literal_expression_inheritance = {
	.evaluate = literal_expression_evaluate,
	.get_references = literal_expression_get_references,
	.free = free_literal_expression,
};



#include "evaluate.h"
#include "get_references.h"
#include "inheritance.h"
#include "free.h"

struct expression_inheritance binary_expression_inheritance = {
	.evaluate = binary_expression_evaluate,
	.get_references = binary_expression_get_references,
	.free = free_binary_expression,
};



#include "inheritance.h"
#include "free.h"

struct expression_inheritance binary_expression_inheritance = {
	.free = free_binary_expression,
};



#include "../struct.h"

#include "kind.h"

struct binary_expression
{
	struct expression super;
	
	enum binary_expression_kind kind;
	
	struct expression* left;
	struct expression* right;
};


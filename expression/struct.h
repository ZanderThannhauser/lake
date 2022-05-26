
#include "kind.h"

struct expression
{
	enum expression_kind kind;
	struct expression_inheritance* inheritance;
};


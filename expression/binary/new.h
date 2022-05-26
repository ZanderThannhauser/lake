
#include "kind.h"

struct expression;

int new_binary_expression(
	struct expression** out,
	enum binary_expression_kind kind,
	struct expression* left,
	struct expression* right);


struct expression;
struct strset;

int binary_expression_get_references(
	struct expression* this,
	struct strset* references);

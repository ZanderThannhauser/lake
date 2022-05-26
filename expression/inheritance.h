
struct expression;

struct expression_inheritance
{
	void (*evaluate)(struct expression*);
	void (*print)(struct expression*);
	void (*free)(struct expression*);
};


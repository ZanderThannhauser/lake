
struct strset;

struct expression;

struct scope;

struct expression_inheritance
{
	double (*evaluate)(struct expression*, struct scope*);
	
	int (*get_references)(struct expression*, struct strset*);
	
	void (*print)(struct expression*);
	
	void (*free)(struct expression*);
};


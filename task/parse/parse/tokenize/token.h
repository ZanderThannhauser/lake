
enum token
{
	t_EOF,
	
	// symbols:
	t_add,
	t_subtract,
	t_multiply,
	t_divide,
	t_remainder,
	t_exponential,
	t_equals,
	t_semicolon,
	
	// brackets:
	t_open_paren, t_close_paren,
	
	// keywords:
	t_include,
	t_let,
	
	// special:
	t_identifier,
	t_literal,
	t_string_literal,
	
	number_of_tokens,
};

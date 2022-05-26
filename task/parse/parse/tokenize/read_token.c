
#include <assert.h>
#include <debug.h>

#include <memory/srealloc.h>

#include "scanner.h"
#include "read_char.h"
#include "read_token.h"

static const enum state {
	s_error,
	
	s_EOF,
	
	// symbols:
	s_plus,
	s_minus,
	s_asterisk,
	s_double_asterisk,
	s_slash,
	s_equals,
	s_semicolon,
	
	// brackets:
	s_open_paren,
	s_close_paren,
	
	// identifer:
	s_identifier,
	
	// literal:
	s_literal,
	s_string_literal,
	
	// keywords:
	s_let,
	s_include,
	
	s_start,
	
	// single-line comment:
	s_ignoring_till_newline,
	
	// symbols:
	s_after_plus,
	s_after_minus,
	s_after_asterisk,
	s_after_double_asterisk,
	s_after_slash,
	s_after_equals,
	s_after_semicolon,
	
	// brackets:
	s_after_open_paren,
	s_after_close_paren,
	
	// identifier:
	s_reading_identifier,
	
	// literal:
	s_reading_literal,
	s_reading_decimal,
	s_reading_string_literal,
	s_reading_string_escape,
	s_after_string_literal,
	
	// keywords:
	s_after_l,
	s_after_le,
	s_after_let,
	
	s_after_i,
	s_after_in,
	s_after_inc,
	s_after_incl,
	s_after_inclu,
	s_after_includ,
	s_after_include,
	
	number_of_states,
} lookup[number_of_states][128] = {
	
	#define ANY 0 ... 127
	
	// EOF:
	[s_start]['\0'] = s_EOF,
	
	// skip whitespace:
	[s_start][' '] = s_start,
	[s_start]['\t'] = s_start,
	[s_start]['\n'] = s_start,
	
	// single-line comment:
	[s_ignoring_till_newline][ANY] = s_ignoring_till_newline,
	[s_ignoring_till_newline]['\n'] = s_start,
	
	// symbols:
	[s_start]['+'] = s_after_plus,
		[s_after_plus][ANY] = s_plus,
	[s_start]['-'] = s_after_minus,
		[s_after_minus][ANY] = s_minus,
	[s_start]['*'] = s_after_asterisk,
		[s_after_asterisk][ANY] = s_asterisk,
		[s_after_asterisk]['*'] = s_after_double_asterisk,
			[s_after_double_asterisk][ANY] = s_double_asterisk,
	[s_start]['/'] = s_after_slash,
		[s_after_slash][ANY] = s_slash,
		[s_after_slash]['/'] = s_ignoring_till_newline,
	[s_start]['='] = s_after_equals,
		[s_after_equals][ANY] = s_equals,
	[s_start][';'] = s_after_semicolon,
		[s_after_semicolon][ANY] = s_semicolon,
	
	// brackets:
	[s_start]['('] = s_after_open_paren,
		[s_after_open_paren][ANY] = s_open_paren,
	[s_start][')'] = s_after_close_paren,
		[s_after_close_paren][ANY] = s_close_paren,
	
	// identifier:
	[s_start]['a' ... 'z'] = s_reading_identifier,
	[s_start]['A' ... 'Z'] = s_reading_identifier,
		[s_reading_identifier][    ANY    ] = s_identifier,
		[s_reading_identifier]['a' ... 'z'] = s_reading_identifier,
		[s_reading_identifier]['A' ... 'Z'] = s_reading_identifier,
	
	// "let" keyword:
	[s_start]['l'] = s_after_l,
		[s_after_l][ANY] = s_reading_identifier,
		[s_after_l]['e'] = s_after_le,
			[s_after_le][ANY] = s_reading_identifier,
			[s_after_le]['t'] = s_after_let,
				[s_after_let][ANY] = s_let,
				[s_after_let]['a' ... 'z'] = s_reading_identifier,
				[s_after_let]['A' ... 'Z'] = s_reading_identifier,
	
	// "include" keyword:
	[s_start]['i'] = s_after_i,
		[s_after_i][ANY] = s_reading_identifier,
		[s_after_i]['n'] = s_after_in,
			[s_after_in][ANY] = s_reading_identifier,
			[s_after_in]['c'] = s_after_inc,
				[s_after_inc][ANY] = s_reading_identifier,
				[s_after_inc]['l'] = s_after_incl,
					[s_after_incl][ANY] = s_reading_identifier,
					[s_after_incl]['u'] = s_after_inclu,
						[s_after_inclu][ANY] = s_reading_identifier,
						[s_after_inclu]['d'] = s_after_includ,
							[s_after_includ][ANY] = s_reading_identifier,
							[s_after_includ]['e'] = s_after_include,
								[s_after_include][ANY] = s_include,
								[s_after_include]['a' ... 'z'] = s_reading_identifier,
								[s_after_include]['A' ... 'Z'] = s_reading_identifier,
	
	// literal:
	[s_start]['0' ... '9'] = s_reading_literal,
		[s_reading_literal][    ANY    ] = s_literal,
		[s_reading_literal][    '.'    ] = s_reading_decimal,
			[s_reading_decimal][    ANY    ] = s_literal,
			[s_reading_decimal]['0' ... '9'] = s_reading_decimal,
		[s_reading_literal]['0' ... '9'] = s_reading_literal,
	
	// string literal:
	[s_start]['\"'] = s_reading_string_literal,
		[s_reading_string_literal][ANY] = s_reading_string_literal,
		[s_reading_string_literal]['\"'] = s_after_string_literal,
			[s_after_string_literal][ANY] = s_string_literal,
		[s_reading_string_literal]['\\'] = s_reading_string_escape,
			[s_reading_string_escape]['n'] = s_reading_string_literal,
			[s_reading_string_escape]['r'] = s_reading_string_literal,
			[s_reading_string_escape]['t'] = s_reading_string_literal,
			[s_reading_string_escape]['b'] = s_reading_string_literal,
};

static int append_tokenchar(struct scanner* this, char c)
{
	int error = 0;
	
	if (this->tokenchars.n + 1 >= this->tokenchars.cap)
	{
		this->tokenchars.cap = this->tokenchars.cap * 2 ?: 1;
		error = srealloc((void**) &this->tokenchars.chars, this->tokenchars.cap);
	}
	
	if (!error)
	{
		this->tokenchars.chars[this->tokenchars.n++] = c;
	}
	
	return error;
}

int read_token(struct scanner* this)
{
	int error = 0;
	ENTER;
	
	dpvc(this->c);
	
	this->tokenchars.n = 0;
	
	enum state state = s_start;
	
	while (!error && state >= s_start)
	{
		state = lookup[state][(unsigned) this->c];
		
		if (state > s_start)
			error = append_tokenchar(this, this->c);
		else if (state == s_start)
			this->tokenchars.n = 0;
		
		if (state >= s_start)
			error = read_char(this);
	}
	
	if (!error)
	switch (state)
	{
		case s_error:
			TODO;
			break;
		
		case s_EOF:
			this->token = t_EOF;
			break;
		
		// symbols:
		case s_plus: this->token = t_add; break;
		case s_minus: TODO; break;
		case s_asterisk: this->token = t_multiply; break;
		case s_double_asterisk: this->token = t_exponential; break;
		case s_slash: this->token = t_divide; break;
		case s_semicolon: this->token = t_semicolon; break;
		
		case s_equals: this->token = t_equals; break;
		
		// brackets:
		case s_open_paren: this->token = t_open_paren; break;
		case s_close_paren: this->token = t_close_paren; break;
		
		// identifer:
		case s_identifier:
		{
			error = append_tokenchar(this, '\0');
			
			dpvs(this->tokenchars.chars);
			
			this->token = t_identifier;
			break;
		}
		
		// literal:
		case s_literal:
		{
			error = append_tokenchar(this, '\0');
			
			dpvs(this->tokenchars.chars);
			
			this->token = t_literal;
			break;
		}
		
		case s_string_literal:
		{
			char
				*w = this->tokenchars.chars,
				*r = w + 1,
				*e = w + this->tokenchars.n - 2;
			
			while (r < e)
				if (*r != '\\')
					*w++ = *r++;
				else switch (*++r)
				{
					case 'n': *w++ = '\n'; break;
					case 'r': *w++ = '\r'; break;
					case 't': *w++ = '\t'; break;
					case 'b': *w++ = '\b'; break;
					default: TODO;
				}
			
			*w = '\0';
			
			dpvs(this->tokenchars.chars);
			
			this->token = t_string_literal;
			break;
		}
		
		// "let" keyword:
		case s_let:
			this->token = t_let;
			break;
		
		// "include" keyword:
		case s_include:
			this->token = t_include;
			break;
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return error;
}







































#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <assert.h>

#include <enums/error.h>

#include <defines/argv0.h>

#include <debug.h>

#include <memory/sstrdup.h>

#include <expression/variable/new.h>
#include <expression/binary/new.h>
#include <expression/literal/new.h>
#include <expression/free.h>

#include "tokenize/scanner.h"
#include "tokenize/read_token.h"

#include "read_expression.h"

static int read_highest_expression(struct expression** out, struct scanner* scanner)
{
	int error = 0;
	ENTER;
	
	switch (scanner->token)
	{
		case t_literal:
		{
			char* m;
			double value;
			
			dpvs(scanner->tokenchars.chars);
			
			if (errno = 0, value = strtod(scanner->tokenchars.chars, &m), errno || *m)
				fprintf(stderr, "%s: strtod(): %m\n", argv0),
				error = e_bad_input_file;
			else error = 0
				?: new_literal_expression(out, value)
				?: read_token(scanner);
			
			break;
		}
		
		case t_open_paren:
		{
			error = 0
				?: read_token(scanner)
				?: read_expression(out, scanner)
				?: read_token(scanner);
			
			break;
		}
		
		case t_identifier:
		{
			char* dup = NULL;
			
			error = 0
				?: sstrdup(&dup, scanner->tokenchars.chars)
				?: new_variable_expression(out, dup)
				?: read_token(scanner);
			
			if (error)
				free(dup);
			
			break;
		}
		
		default:
			TODO;
			break;
	}
	
	EXIT;
	return error;
}

static int read_expo_expression(struct expression** out, struct scanner* scanner)
{
	int error = 0;
	ENTER;
	
	struct expression* left = NULL;
	
	error = read_highest_expression(&left, scanner);
	
	while (!error && scanner->token == t_exponential)
	{
		error = read_token(scanner);
		
		struct expression* right = NULL, *new;
		
		error = 0
			?: read_expo_expression(&right, scanner)
			?: new_binary_expression(&new, bek_exponential, left, right);
		
		if (error)
			free_expresssion(right);
		else
			left = new;
	}
	
	if (error)
		free_expresssion(left);
	else
		*out = left;
	
	EXIT;
	return error;
}

static int read_multiplicative_expression(struct expression** out, struct scanner* scanner)
{
	int error = 0;
	ENTER;
	
	struct expression* left = NULL;
	
	error = read_expo_expression(&left, scanner);
	
	while (!error && (false
		|| scanner->token == t_multiply
		|| scanner->token == t_divide
		|| scanner->token == t_remainder))
	{
		enum token operator = scanner->token;
		
		error = read_token(scanner);
		
		if (!error)
		switch (operator)
		{
			case t_multiply:
			{
				struct expression* right = NULL, *new;
				
				error = 0
					?: read_expo_expression(&right, scanner)
					?: new_binary_expression(&new, bek_multiply, left, right);
				
				if (error)
					free_expresssion(right);
				else
					left = new;
				
				break;
			}
			
			case t_divide:
			{
				struct expression* right = NULL, *new;
				
				error = 0
					?: read_expo_expression(&right, scanner)
					?: new_binary_expression(&new, bek_divide, left, right);
				
				if (error)
					free_expresssion(right);
				else
					left = new;
				
				break;
			}
			
			case t_remainder:
				TODO;
				break;
			
			default:
				TODO;
				break;
		}
	}
	
	if (error)
		free_expresssion(left);
	else
		*out = left;
	
	EXIT;
	return error;
}

static int read_additive_expression(struct expression** out, struct scanner* scanner)
{
	int error = 0;
	ENTER;
	
	struct expression* left = NULL;
	
	error = read_multiplicative_expression(&left, scanner);
	
	while (!error && (false
		|| scanner->token == t_add
		|| scanner->token == t_subtract))
	{
		enum token operator = scanner->token;
		
		error = read_token(scanner);
		
		if (!error)
		switch (operator)
		{
			case t_add:
			{
				struct expression* right = NULL, *new;
				
				error = 0
					?: read_multiplicative_expression(&right, scanner)
					?: new_binary_expression(&new, bek_add, left, right);
				
				if (error)
					free_expresssion(right);
				else
					left = new;
				
				break;
			}
			
			case t_subtract:
				TODO;
				break;
			
			default:
				TODO;
				break;
		}
	}
	
	if (error)
		free_expresssion(left);
	else
		*out = left;
	
	EXIT;
	return error;
}

int read_expression(struct expression** out, struct scanner* scanner)
{
	int error = 0;
	ENTER;
	
	error = read_additive_expression(out, scanner);
	
	EXIT;
	return error;
}












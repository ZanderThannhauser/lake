
#include <unistd.h>
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>
#include <fcntl.h>

#include <defines/argv0.h>

#include <enums/error.h>

#include <debug.h>

#include "tokenize/scanner.h"
#include "tokenize/read_char.h"
#include "tokenize/read_token.h"

#include "read_let.h"
#include "read_include.h"
#include "parse.h"

int parse(const char* dirpath, int fd, struct pqueue* pqueue)
{
	int error = 0;
	ENTER;
	
	// cpu lock;
	
	struct scanner scanner = {.fd = fd};
	
	error = 0
		?: read_char(&scanner)
		?: read_token(&scanner);
	
	while (scanner.token != t_EOF)
	{
		switch (scanner.token)
		{
			case t_let:
				error = read_let(&scanner, pqueue);
				break;
			
			case t_include:
				error = read_include(&scanner, dirpath, pqueue);
				break;
			
			default:
				TODO;
				break;
		}
	}
	
	// cpu unlock
	
	free(scanner.tokenchars.chars);

	EXIT;
	return error;
}












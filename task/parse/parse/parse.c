
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

int parse(const char* input_path, struct pqueue* pqueue)
{
	int error = 0;
	int fd = -1;
	ENTER;
	
	dpvs(input_path);
	
	if ((fd = open(input_path, O_RDONLY)) < 0)
		fprintf(stderr, "%s: open(\"%s\"): %m\n", argv0, input_path),
		error = e_bad_input_file;
	else
	{
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
					error = read_include(&scanner, pqueue);
					break;
				
				default:
					TODO;
					break;
			}
		}
		
		// cpu unlock
		
		free(scanner.tokenchars.chars);
	}
	
	if (fd > 0) close(fd);
	
	EXIT;
	return error;
}













#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <debug.h>

#include <enums/error.h>

#include <defines/argv0.h>

#include "scanner.h"
#include "read_char.h"

int read_char(struct scanner* this)
{
	int error = 0;
	ssize_t rr;
	ENTER;
	
	if (this->chunk.i < this->chunk.n)
		this->c = this->chunk.buffer[this->chunk.i++];
	// cpu unlock;
	else if ((rr = read(this->fd, this->chunk.buffer, sizeof(*this->chunk.buffer))) < 0)
		fprintf(stderr, "%s: read(): %m\n", argv0),
		error = e_syscall_failed;
	// cpu lock;
	else if (!rr)
		this->c = '\0';
	else
	{
		this->chunk.i = 0, this->chunk.n = rr;
		this->c = this->chunk.buffer[this->chunk.i++];
	}
	
	if (!error)
	{
		dpvc(this->c);
	}
	
	EXIT;
	return error;
}



#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <limits.h>
#include <unistd.h>

#include <defines/argv0.h>

#include <debug.h>

#include <enums/error.h>

#include "parse/parse.h"

#include "struct.h"
#include "process.h"

int parse_task_process(struct task* super, struct pqueue* pqueue)
{
	int error = 0, fd = -1;
	char dirpath[PATH_MAX], *slash;
	struct parse_task* const this = (struct parse_task*) super;
	ENTER;
	
	dpvs(this->input_path);
	
	if ((slash = rindex(this->input_path, '/')))
	{
		unsigned len = slash - this->input_path;
		
		strncpy(dirpath, this->input_path, len);
		
		dirpath[len] = '\0';
	}
	else
	{
		strcpy(dirpath, ".");
	}
	
	dpvs(dirpath);
	
	if ((fd = open(this->input_path, O_RDONLY)) < 0)
		fprintf(stderr, "%s: open(\"%s\"): %m\n", argv0, this->input_path),
		error = e_bad_input_file;
	else
		error = parse(dirpath, fd, pqueue);
	
	if (fd > 0) close(fd);
	
	EXIT;
	return error;
}














#include <string.h>

#include <debug.h>

#include "struct.h"
#include "compare.h"

int compare_parse_task(
	const struct task* super_a,
	const struct task* super_b)
{
	int cmp = 0;
	const struct parse_task* const a = (struct parse_task*) super_a;
	const struct parse_task* const b = (struct parse_task*) super_b;
	ENTER;
	
	dpvs(a->input_path);
	dpvs(b->input_path);
	
	cmp = strverscmp(a->input_path, b->input_path);
	
	dpv(cmp);
	
	EXIT;
	return cmp;
}



#include <stdio.h>
#include <math.h>
#include <debug.h>

#include <defines/CSI.h>

#include <misc/hsv_to_rgb.h>

#include "struct.h"
#include "print.h"

void parse_task_print(struct task* super)
{
	struct parse_task* const this = (struct parse_task*) super;
	ENTER;
	
	struct rgb color = hsv_to_rgb(M_PI * super->kind / number_of_task_kinds, 1, 1);
	
	printf(
		CSI "38;2;%hhu;%hhu;%hhu" "m" // set 256-bit foreground color
		"parsing '%s'..."
		CSI "m", // reset all attributes to their defaults
		color.red, color.green, color.blue,
		this->input_path
	);
	
	#ifndef RELEASE
	puts("");
	#endif
	
	EXIT;
}


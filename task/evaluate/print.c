
#include <stdio.h>
#include <assert.h>

#include <math.h>
#include <debug.h>

#include <defines/CSI.h>

#include <misc/hsv_to_rgb.h>

#include "struct.h"
#include "print.h"

void evaluate_task_print(struct task* super)
{
	struct evaluate_task* const this = (struct evaluate_task*) super;
	ENTER;
	
	struct rgb color = hsv_to_rgb(M_PI * tk_evaluate / number_of_task_kinds, 1, 1);
	
	printf(
		CSI "38;2;%hhu;%hhu;%hhu" "m" // set 256-bit foreground color
		"evaluating '%s'..."
		CSI "m", // reset all attributes to their defaults
		color.red, color.green, color.blue,
		this->name
	);
	
	#ifndef RELEASE
	puts("");
	#endif
	
	EXIT;
}


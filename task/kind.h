
#ifndef ENUM_TASK_KIND
#define ENUM_TASK_KIND

enum task_kind
{
	tk_shutdown,
	
	tk_parse,
	
	tk_dependency,
	
	tk_evaluate,
	
	tk_wake_up,
	
	number_of_task_kinds,
};

#endif

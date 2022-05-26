
#ifndef ENUM_TASK_KIND
#define ENUM_TASK_KIND

enum task_kind
{
	tk_error,
	
	tk_parse,
	
	tk_dependency,
	
	tk_evaluate,
	
	tk_exit,
	
	number_of_task_kinds,
};

#endif

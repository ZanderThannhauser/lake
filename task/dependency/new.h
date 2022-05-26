
struct task;
struct expression;

int new_dependency_task(
	struct task** out,
	char* name,
	struct expression* expression);

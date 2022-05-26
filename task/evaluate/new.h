
struct task;
struct expression;

int new_evaluate_task(
	struct task** out,
	char* name,
	struct expression* expression);

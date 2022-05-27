
struct scope;
struct scheduler;
struct task;

int parse_task_process(
	struct task* super,
	struct pqueue* pqueue,
	struct scheduler*,
	struct scope* scope);

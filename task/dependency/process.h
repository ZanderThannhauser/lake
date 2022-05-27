
struct scope;
struct scheduler;
struct task;
struct pqueue;

int dependency_task_process(
	struct task* super,
	struct pqueue* pqueue,
	struct scheduler* scheduler,
	struct scope* scope);

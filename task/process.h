
struct pqueue;
struct task;
struct scheduler;
struct scope;

int task_process(struct task* super,
	struct pqueue* pqueue,
	struct scheduler* scheduler,
	struct scope* scope);

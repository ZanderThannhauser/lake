
struct task;
struct pqueue;
struct scheduler;

int evaluate_task_process(struct task* super, struct pqueue* pqueue, struct scheduler*,
	struct scope* scope);

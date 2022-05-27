
struct scheduler;
struct strset;
struct task;

int scheduler_schedule(
	struct scheduler* this,
	struct strset* references,
	struct task* task);


struct task;
struct scheduler_bundle;

int new_scheduler_bundle(
	struct scheduler_bundle** out,
	struct task* task);

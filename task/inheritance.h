
struct scope;
struct pqueue;
struct task;
struct scheduler;

struct task_inheritance
{
	int (*process)(
		struct task*,
		struct pqueue*,
		struct scheduler*,
		struct scope* scope);
	int (*compare)(const struct task*, const struct task*);
	void (*print)(struct task*);
	void (*free)(struct task*);
};


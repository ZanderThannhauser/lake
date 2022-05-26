
struct pqueue;
struct task;

struct task_inheritance
{
	int (*process)(struct task*, struct pqueue*);
	int (*compare)(const struct task*, const struct task*);
	void (*print)(struct task*);
	void (*free)(struct task*);
};



struct strset;

int strset_foreach(struct strset* this, int (*callback)(char*));

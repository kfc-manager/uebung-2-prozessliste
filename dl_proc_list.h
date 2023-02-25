#include <stddef.h>

typedef struct dl_proc_list {
	struct dl_proc_list* pred;
	struct dl_proc_list* succ;
	int pid;
	int ppid;
} dl_proc_list;

dl_proc_list* dl_proc_list_create();

int dl_proc_list_insert(dl_proc_list *list, int pid);

int dl_proc_list_get(dl_proc_list *list, int position, int* pid, int* ppid);

int dl_proc_list_remove(dl_proc_list *list, int pid);

void dl_proc_list_free(dl_proc_list *list);


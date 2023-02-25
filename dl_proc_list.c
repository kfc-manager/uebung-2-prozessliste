#include "dl_proc_list.h"
#include <stdlib.h>
#include <stdio.h>

dl_proc_list* dl_proc_list_create() {
	dl_proc_list *list = malloc(sizeof(dl_proc_list));
	if (!list) return NULL;
	list->pred = NULL;
	list->succ = NULL;
	int pid = 1;
	int ppid = 0;
	list->pid = pid;
	list->ppid = ppid;
	return list;
}

int dl_proc_list_insert(dl_proc_list *list, int pid) {
	dl_proc_list *akt = list;
	while (akt->succ != NULL) {
		if (akt->pid == pid) return -2; //a process already uses that pid
		akt = akt->succ;
	}
	if (akt->pid == pid) return -2; //last process already uses that pid
	int ppid = akt->pid; //biggest pid in list
	akt = list;
	while (akt->succ != NULL && akt->succ->pid < pid) { //now find position where we have to insert
		akt = akt->succ;
	}
	dl_proc_list *tmp = akt->succ; //save old successor, so we can append it later
	akt->succ = calloc(1,sizeof(dl_proc_list)); //create new element
       	if (!akt->succ) return -1; //couldn't allocate storage for the new element
	akt->succ->pred = akt;
	if (tmp != NULL) tmp->pred = akt->succ;
	akt->succ->succ = tmp;
	akt->succ->pid = pid;
	akt->succ->ppid = ppid;
	return 0;
}

int dl_proc_list_get(dl_proc_list *list, int position, int* pid, int* ppid) {
	dl_proc_list *akt = list;
	if (!list) return -1;
	for (int i = 0; i < position; i++) {
		if (akt->succ == NULL) return -1; //position is out of list range
		akt = akt->succ;
	}
	*pid = akt->pid;
	*ppid = akt->ppid;
	return 0;
}

int dl_proc_list_remove(dl_proc_list *list, int pid) {
	dl_proc_list *akt = list;
	if (pid == 1) return -2; //process with pid = 1 can't be removed
	while (akt->succ != NULL) {
		if (akt->pid == pid) break;
		akt = akt->succ;
	}
	if (akt->succ == NULL && akt->pid != pid) return -1; //no process has that pid
	int ppid = akt->ppid; //save ppid so we can change ppid of child process'
	akt->pred->succ = akt->succ;
	if (akt->succ != NULL) akt->succ->pred = akt->pred; //removed element wasn't the last element
	free(akt);
	akt = list;
	while (akt->succ == NULL) {
		if (akt->ppid == pid) akt->ppid = ppid; //found element of that we have to set new ppid
		akt = akt->succ;
	}
	if (akt->ppid == pid) akt->ppid = ppid; //also check for last element
	return 0;
}

void dl_proc_list_free(dl_proc_list *list) {
	dl_proc_list *akt = list;
	dl_proc_list *next;
	while (akt != NULL) {
		next = akt->succ;
		free(akt);
		akt = next;
	}
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dl_proc_list.h"


int main(int argc, char** argv) {
	dl_proc_list *list = dl_proc_list_create();
	if (!list) {
		fprintf(stderr,"Couldn't allocate Doubly Linked List!\n");
		exit(EXIT_FAILURE);
	}
	int count = 1;
	for (int i = 1; i < argc; i++) {
		char *rest;
		long int entry = strtol(argv[i],&rest,10);
		if (strlen(rest) != 0UL) {
			printf("Warnung: Ungueltiges Argument \"%s\" ignoriert.\n",rest);
			continue;
		}
		if (entry > 0L) {
			int status = dl_proc_list_insert(list,entry);
			if (status == -2) {
				printf("Fehler beim Einfuegen: PID %ld existiert bereits.\n", entry);
				continue;
			} else if (status == -1) {
				fprintf(stderr,"Something went wrong while allocating an element!\n");
				exit(EXIT_FAILURE);
			}
			count++;
		} else if (entry < 0L) {
			entry *= -1;
			int status = dl_proc_list_remove(list,entry);
			if (status == -2) {
				printf("Fehler: Prozess mit ID = 1 kann nicht geloescht werden.\n");
				continue;
			} else if (status == -1) {
				printf("Fehler beim Loeschen: Prozess mit ID = %ld existiert nicht.\n",entry);
				continue;
			}
			count--;
		}
	}	
	int pid;
	int ppid;
	for (int i = 0; i < count; i++) {
		int status = dl_proc_list_get(list,i,&pid,&ppid);
		if (status < 0) {
			fprintf(stderr, "Something went wrong while looping through the list!\n");
			exit(EXIT_FAILURE);
		}
		printf("PID: %d, ",pid);
		printf("Parent PID: %d\n",ppid);
	}
	dl_proc_list_free(list);
	return 0;
}


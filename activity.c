#include "header.h"
#define MAX_PROCESSES 1024

extern process_act p_list[1024];
extern int p_count ;
extern int stdout_global;

// Function to update process state
void update_process_state(int i) {
    char path[4096], line[4096], *token;
    FILE *status_file;
    
    sprintf(path, "/proc/%d/status", p_list[i].pid);
  
    status_file = fopen(path, "r");
    if (!status_file) {
         //strcpy(p_list[i].state, "Running");
        return;
    }

    
    
   
    while (fgets(line,sizeof(line), status_file)) {

        if (strncmp(line, "State:", 6) == 0) {
           
            char state_code = line[7];
            //printf("state code: %c\n", state_code);
             if (state_code == 'T') {
                strcpy(p_list[i].state, "Stopped");
            } else {
                strcpy(p_list[i].state, "Running");
            }
        }
    }

    fclose(status_file);

    }


// Function to remove a process from the list
void remove_process(int pid) {
    int it;
    int found = 0;
    for(int i=0; i < p_count; i++)
    {
        if(p_list[i].pid == pid)
        {
            it=i ; 
            found = 1;
            break;
        }
    }
    if (found) {
        for(int j=it; j < p_count-1; j++)
        {
            p_list[j].pid = p_list[j+1].pid;
           // dprintf(stdout_global,"name: %s %s\n",p_list[j].name,p_list[j+1].name);
            strcpy(p_list[j].name, p_list[j+1].name);
        }
        p_count--;
    }
}
 
int compare_processes(const void *a, const void *b) {
    process_act *pa = (process_act *)a;
    process_act *pb = (process_act *)b;
    return strcmp(pa->name, pb->name);
}

// Function to print the list of processes
void print_activities() {
    qsort(p_list, p_count, sizeof(process_act), compare_processes);
    for (int i = 0; i < p_count; i++) {
        
        update_process_state(i);
        dprintf(stdout_global,"%d : %s - %s\n", p_list[i].pid, p_list[i].name, p_list[i].state);
    }
    
}

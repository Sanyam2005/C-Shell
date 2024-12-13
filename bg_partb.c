#include "header.h"
extern int p_count;
extern process_act p_list[1024];


// bg command function
void bg_partb(pid_t pid) {
    int found = 0;
    int index = -1;

    // Search for the process in the job list
    for (int i = 0; i < p_count; i++) {
        if (p_list[i].pid == pid) {
            found = 1;
            index = i;
            break;
        }
    }

    if (!found) {
        printf("No such process found\n");
        return;
    }

    // Send SIGCONT signal to resume the stopped process
    if (kill(pid, SIGCONT) == -1) {
        perror("Failed to send SIGCONT");
        return;
    }
    // signal(SIGINT, SIG_IGN);
   
}

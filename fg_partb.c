#include "header.h"
extern int p_count;
extern process_act p_list[1024];
extern pid_t fgpid;
extern int stdout_global;
extern char *last_process;
extern int last_time;
extern Process last_processes[100];
extern int num_processes ;
extern char curprocess[4096];
void fg_partb(int pid) {
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
        dprintf(stdout_global,"No such process found\n");
        return;
    }

    if(kill(pid, SIGCONT) == -1){
        perror("Failed to send SIGCONT");
        return;
    }

    fgpid = pid;
    
    strcpy(curprocess, p_list[index].name);
    // for(int j=index; j < p_count-1; j++)
    //     {
    //         p_list[j].pid = p_list[j+1].pid;
    //         strcpy(p_list[j].name, p_list[j+1].name);
    //     }
    // p_count--;
    remove_process(pid);
    dprintf(stdout_global,"Process with PID %d is in the foreground\n", pid);
    
    struct timeval start, end;
    gettimeofday(&start, NULL);

    int status;
    pid_t wc = waitpid(pid, &status, WUNTRACED);
    if (wc == -1) {
        perror("waitpid");
        return;
    }

    gettimeofday(&end, NULL);
        long seconds = (end.tv_sec - start.tv_sec);
        //printf("%f",duration);
        if (seconds > 2.0 && num_processes < 100) {
            last_processes[num_processes].name = strdup(curprocess);
            last_processes[num_processes].time = (int)seconds;
            num_processes++;
        }
}

// void fg_pawefrtb(int pid){
//     if(kill(pid, SIGCONT) == -1){
//         perror("Failed to send SIGCONT");
//         return;
//     }
        
//     fgpid = pid;
//     int found = 0;
//     int index = -1;

//     // Search for the process in the job list
//     for (int i = 0; i < p_count; i++) {
//         if (p_list[i].pid == pid) {
//             found = 1;
//             index = i;
//             break;
//         }
//     }

//     if (!found) {
//         dprintf(stdout_global,"No such process found\n");
//         return;
//     }
//     dprintf(stdout_global,"Process with PID %d is in the foreground\n", pid);
//     int status;
//     pid_t wc = waitpid(pid, &status, WUNTRACED);
//     if (wc == -1) {
//         perror("waitpid");
//         return;
//     }
            
//     return 0;
            
 //   }

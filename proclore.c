#include "header.h"

void proclore(pid_t pid) {
    char path[4096];
    char status[4096];
    char state[4096];
    char exec_path[4096];
    long int vmsize;

    sprintf(path, "/proc/%d/status", pid);
    FILE *fp = fopen(path, "r");
    if (fp == NULL) {
        printf("Proclore error(the process does not exist)\n");
        return;
    }
    //print pid
    printf("Pid: %d\n",pid);

    //print process group
    pid_t pgid = getpgid(pid);
    if (pgid < 0) {
        perror("getpgid");
        return;
    }
    printf("Process Group: %d\n", pgid);

   
   

    //print state and vmsize using status file
    while (fgets(status, sizeof(status), fp) != NULL) {
        
         if (strncmp(status, "State:", 6) == 0) {
            pid_t check = tcgetpgrp(STDIN_FILENO);
           if (pgid == pid &&(status[7]=='R' || status[7]=='S')&&check==pid) {
            printf("State: %c+\n",status[7]);
            } else {
              printf("State: %c\n",status[7]);
            }
        }
        else if (strncmp(status, "VmSize:", 7) == 0) {
            printf("%s", status);
        }
    }

    fclose(fp);
   
    //print executable path
    sprintf(path, "/proc/%d/exe", pid);
    ssize_t len = readlink(path, exec_path, sizeof(exec_path) - 1);
    if (len != -1) {
        exec_path[len] = '\0';
        printf("Executable Path: %s\n", exec_path);
    } else {
        perror("Ececutable path");
    }

    
}

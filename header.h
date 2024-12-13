#ifndef HEADER_H
#define HEADER_H

#include<stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <errno.h>
#include <signal.h>
#include <pwd.h>
#include <limits.h>
#include <time.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <dirent.h> 
#include <pwd.h>
#include <grp.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
typedef struct {
    int pid;
    char name[4096];
    char state[16];  // Running or Stopped
} process_act;

typedef struct {
    char *name;
    int time;
} Process;
void monitor_background_processes() ;
void processinput(char *cmd);
void proclore(pid_t pid);
void child_handler(int sig);
void bg(char **and_args,int no_args);
void fg(char **and_args,int no_args);
void seek(char **flags,int n, char *search, char *target_dir);
void handle_sigchld(int sig);
void update_process_state(int i);
void add_process(int pid, const char *command);
void remove_process(int pid);
void print_activities();
void process_ping(int pid, int signal);
void fg_partb(int pid);
void bg_partb(int pid);
void iman(char* cmd);
int checkalias(char* input);
#endif 
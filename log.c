#include "header.h"
#include "log.h"
#include <stdbool.h>
#include <ctype.h>
#define MAX 16

extern char *univ_home;
char commands[MAX][4096];
int start = 0;
int end = 0;

void load_commands() {
    char logpath[4096];
    sprintf(logpath, "%s/log.txt", univ_home);
   
    FILE *file = fopen(logpath, "r");
    if (file==NULL) {
        return;
    }

    char cmd[4096];
    while (fgets(cmd, sizeof(cmd), file)!=NULL) {
        cmd[strcspn(cmd, "\n")] = '\0'; // Remove newline character
        strcpy(commands[end], cmd);
        end = (end + 1) % MAX;
       // printf("%d : %d, ",start,end);
        if (end == start) {
            start = (start + 1) % MAX;
        }
    }
    fclose(file);
}
bool is_duplicate(const char *command) {
    
    if (end == start) {
        return false;
    }
    int lastindex;
    if(end==0){
        lastindex=MAX-1;
    }
    else{
        lastindex=end-1;
    }
   
    if(strcmp(command, commands[lastindex]) == 0) return true;
    else return false;
  
}
void log_command(char *command) {
    
    if (strcmp(command, "log") == 0) {
        return;
    }
    
    command[strcspn(command, "\n")] = '\0';
     if(is_duplicate(command)==true) {
        return;
    }
    
    strcpy(commands[end], command);
    
    //write command in log.txt
    FILE *file ;
    char logpath[4096];
    sprintf(logpath, "%s/log.txt", univ_home);
    file=fopen(logpath, "a");
    
    if (file==NULL) {
        perror("Failed to open log file");
        return;
    }
   
    fprintf(file, "%s\n", command);

    //fflush(file); 
    fclose(file);
    //update circular buffer
    end = (end + 1) % MAX;

    if (end == start) {
        start = (start + 1) % MAX;
    }
}

void log_purge() {
    start = end = 0;
    FILE *file = fopen("log.txt", "w");
    if (file==NULL) {
        return;
    }
    fclose(file);
    
}

void log_execute(int index) {
   //error checking
  // printf("vegucweuc");
    if (index < 1 || index > MAX || (start <= end && (index < start || index > end)) ) {
        printf("Invalid index\n");
        return;
    }
    index = (end - index + MAX) % MAX;
    // printf("end%d",end);
    // if(index<=end)
    // index=end-index;
    // else
    // index=MAX-(index-end);
    char cmd[4096];
    strcpy(cmd,commands[index]);
    // Execute the command
     strcat(cmd, "\n");
    
     processinput(cmd);
    //  printf("aft %s\n",cmd);

    
}

void print_log() {
   
    if (start==0&&end==0){
        printf("No logs\n");
     return;
    }
    if (start < end) {
        for (int i = start; i < end; i++) {
           
            printf("%s\n", commands[i]);
        }
    } 
    else {
        for (int i = start; i < MAX; i++) {
            printf("%s\n",commands[i]);
        }
        for (int i = 0; i < end; i++) {
            printf("%s\n", commands[i]);
        }
    }
    
}

#include "header.h"
#include "task1.h"
#include <unistd.h>
extern char* last_process;
extern int last_time;
extern Process last_processes[100];
extern int num_processes ;

void task1(const char *univhome) {
    struct passwd *pw;
    pw = getpwuid(getuid());  // get the user name based on used id
    char *username = pw->pw_name;
    
    char hostname[4096];
    gethostname(hostname, sizeof(hostname)); //get hostname

    char cwd[4096];
    getcwd(cwd, sizeof(cwd)); 

    char *rel_path = cwd;
    
    if (strstr(cwd, univhome) == cwd) { //checking if univhome is found anywhere in cwd

        rel_path = cwd + strlen(univhome); //nice trick to get relative path
        if (*rel_path == '\0') {

            rel_path = "~";
        } 
        else {
            
             char new_path[4096];
            snprintf(new_path, sizeof(new_path), "~%s", rel_path);
            rel_path = new_path;
        }
    }
    if(num_processes>0){
        printf("\033[1m\033[32m<%s@%s:%s\033[0m ", username, hostname, rel_path);
        int i=0;
        for(;i<num_processes-1;i++){
            printf("%s %ds ; ",last_processes[i].name,last_processes[i].time);
        }
        printf("%s %ds>",last_processes[i].name,last_processes[i].time);
        num_processes=0;
        
    }
    else
        printf("\033[1m\033[32m<%s@%s:%s>\033[0m ", username, hostname, rel_path);
}
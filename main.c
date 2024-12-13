#include "header.h"
#include "hop.h"
#include "reveal.h"
#include "log.h"


char *univ_home = NULL;
char *univhome = NULL;
char *prevdir = NULL;
char *last_process=NULL;
int last_time=0;
pid_t shellpid;
pid_t fgpid;
char curprocess[4096];
Process last_processes[100];
process_act p_list[1024];
int p_count ;
int num_processes = 0; 
int flag_mhrc = 0;
int stdout_global;

void sig_c(int signum)
{
    if(fgpid > 0) {
        if(kill(fgpid, SIGINT) == -1) {
            perror("Failed to send SIGINT");
            fgpid = -1;
        } else {
            fgpid = -1;  // Reset foreground process ID after sending SIGINT
        }
    }
    printf("\n");
    //printf("ervre");
    fflush(stdout);
    return;
}
 

void handle_sigstop(int sig){
    if(fgpid != -1){
        if(kill(fgpid, SIGSTOP) == -1){
            perror("kill");
            return;
        }
        strcpy(p_list[p_count].name,curprocess);
        p_list[p_count].pid= fgpid;
        p_count++;
        fgpid=-1;
    }
    else{
        fgpid=-1;
    }
    printf("\n");
    return;
}
int main()
{
    stdout_global = dup(STDOUT_FILENO);
    num_processes=0;
    p_count=0;
    char home_cwd[4096];
    fgpid = -1;
    if (getcwd(home_cwd, sizeof(home_cwd)) != NULL) {
        univ_home = malloc(4096 * sizeof(char));
        strcpy(univ_home, home_cwd);   //univ_home holds the path of cwd
    } else {
        perror("getcwd() error");
        exit(1);
    }
    load_commands();
    signal(SIGINT, sig_c);
    signal(SIGTSTP, handle_sigstop);
    signal(SIGCHLD, child_handler);
   
    char input[4096];
    
    while (1)
    {
        task1(univ_home);
       // fflush(stdout);
         if (fgets(input, 4096, stdin) == NULL) {
            printf("\n");
            handle_ctrl_d();
        }
         // Trim the newline character and check if the input is empty
        if (input[0] == '\n' || input[0] == '\0') {
            continue;  
        }
        //check
        
        char *input3 = strdup(input);
        checkalias(input3);
        if(flag_mhrc==0)
        processinput(input);
        flag_mhrc=0;
       free(input3);
        
    }

    return 0;
}
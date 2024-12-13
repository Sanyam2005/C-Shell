#include "header.h"
extern char *last_process;
extern int last_time;
extern Process last_processes[100];
extern int num_processes ;
extern pid_t fgpid;
extern process_act p_list[1024];
extern int p_count ;
extern int stdout_global;
extern char curprocess[4096];


void child_handler(int sig) {
    int status;
    pid_t pid;
    int remove_flag=0;
    while ((pid = waitpid(-1, &status, WNOHANG )) > 0) {
        
        char str[4096];
        int sigflag =0;
        for(int i=0; i < p_count; i++)
        {
            if(p_list[i].pid == pid)
            {
                strcpy(str, p_list[i].name);
                
                sigflag = 1;      
                break;
            }
        }

        if (sigflag==1) {
            if(WIFSTOPPED(status)||WIFCONTINUED(status)){}
            //    // update_state(pid,"Stopped");
            // }
            // else if(){
            //     //update_state(pid,"Running");
            // }
            else{
                if(WIFEXITED(status) && WEXITSTATUS(status) != 0) {
                    dprintf(stdout_global,"\033[31m %s with pid %d exited abnormally\033[0m\n",str, pid);
                }
                else if(WIFSIGNALED(status)){
                    int termsig = WTERMSIG(status);
                    if(termsig==SIGINT) remove_flag=1;
                    else{
                    dprintf(stdout_global,"\033[31m %s with pid %d was terminated by signal %d\033[0m\n", str, pid, WTERMSIG(status));
                    }
                }
                else if(WIFEXITED(status)) {
                    dprintf(stdout_global,"\033[31m %s with pid %d exited normally\033[0m\n",str, pid);
                    
                }         
        
                if(remove_flag==0){
                  //  dprintf(stdout_global,"\033[31m Removing from activities \033[0m\n");
                remove_process(pid);
                }
            }
            // free(command);
        }
    }
        
}
    

void bg(char **and_args,int no_args) {
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
      //  dprintf(stdout_global,"bg %s %s",and_args[0],and_args[1]);
        setpgid(0, 0);
        // signal(SIGINT,SIG_IGN);
        // signal(SIGTSTP,SIG_IGN);
        execvp(and_args[0], and_args);
        perror("Execution failed or invalid command");
        exit(1);
    } else {

         strcpy(p_list[p_count].name, and_args[0]);
         
               for(int i = 1; i < no_args; i++)
               {
                    strcat(p_list[p_count].name, " ");
                    strcat(p_list[p_count].name, and_args[i]);
               }

               p_list[p_count].pid= pid;
               p_count++;
              // print_activities();
        dprintf(stdout_global,"PID: %d\n", pid);
        
        return;
    }
}

void fg(char **and_args,int no_args) {
    struct timeval start, end;
    gettimeofday(&start, NULL);
    pid_t pid = fork();
    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } else if (pid == 0) {
        // for(int i=0;i<sizeof(and_args);i++){
        //     printf("%s\n",and_args[i]);
        // }
        
        setpgid(0, 0);
        execvp(and_args[0], and_args);
        fflush(stdout);
        perror("Execution failed or invalid command");
        exit(1);
    } else {
        int status;
        
         strcpy(curprocess, and_args[0]);
               
        for(int i = 1; i < no_args; i++)
        {
            strcat(curprocess, " ");
            strcat(curprocess, and_args[i]);
        }
        fgpid = pid;
        
        waitpid(pid, &status, WUNTRACED);
        
        gettimeofday(&end, NULL);
        long seconds = (end.tv_sec - start.tv_sec);
        //printf("%f",duration);
        if (seconds > 2.0 && num_processes < 100) {
            last_processes[num_processes].name = strdup(and_args[0]);
            last_processes[num_processes].time = (int)seconds;
            num_processes++;
        }
    }
}


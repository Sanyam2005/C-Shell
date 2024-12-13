#include "header.h"
#include "hop.h"
#include "reveal.h"
#include "log.h"
#include "task1.h"

#define DELIMITERS "\t\n "
// This function will be called when a SIGCHLD signal is received

int check_redirection(char *command)
{
    char *out = strstr(command, ">");
    char *in = strstr(command, "<");
    
    if((out != NULL) || (in != NULL))return 1;
    else return 0;
}

int check_piping(char *cmdcopy)
{
    char *is_pipe = strstr(cmdcopy, "|");
    if(is_pipe != NULL)
        return 1;

    else return 0;
}

 int redir_bgflag = 0;
void processinput(char *cmd) {

   // printf("cmd: %s\n", cmd);
    //  if (signal(SIGCHLD, child_handler) == SIG_ERR) {
    //     perror("signal");
    //     exit(1);
    // }
    //signal(SIGCHLD, handle_sigchld);
   // printf("cmd: %s\n", cmd);
    
    int flag = 0;
    char cmd2[4096];
    strcpy(cmd2,cmd);
    // char *command = strtok(cmd, ";");
     char *p = strtok (cmd, ";");
    char **com_array = malloc(4096 * sizeof(char *));

    int no = 0;

    while (p != NULL)
    {
        com_array[no++] = p;
        p = strtok (NULL, ";");
    }

     //printf("%s,",cmd);
     for (int i = 0; i < no; i++) {
         char *cmd2copy = strdup(com_array[i]);
   // fprintf(stderr,"cmdcopy: %s\n", cmdcopy);
        if(check_piping(cmd2copy)==1){
            piping(cmd2copy);
            continue;
        }
    //     if(check_redirection(cmdcopy)){
    //         redirection(cmdcopy);
    //         continue;
    //     }
        char *a_token = strtok(com_array[i], "&");
        char **cmd_parts = malloc(4096 * sizeof(char *));
        int part_count = 0;

        while (a_token != NULL) {
            cmd_parts[part_count++] = a_token;
            a_token = strtok(NULL, "&");
        }
       for (int j = 0; j < part_count; j++) 
       {
         char *cmdcopy = strdup(cmd_parts[j]);
        
       // fprintf(stderr,"cmdcopy: %s\n", cmdcopy);
       //printf("%d",part_count);
        
        if(check_redirection(cmdcopy)){
            if(part_count>1&&j<part_count-1)
            redir_bgflag = 1;
            redirection(cmdcopy);
            continue;
        }
        char *token = strtok(cmd_parts[j], "\t\n ");
        char *cmd_part = cmd_parts[j];
        int background = (j < part_count - 1);
        char *and_args[4096];
        int and_arg_count = 0;
        while (token != NULL) { 
            
            
                
            if (strcmp(token, "hop") == 0) {
                // Next token is the path
                 int arg_count = 0;
                char *args[4096]; // assuming a maximum of 4096 arguments

                while ((token = strtok(NULL, DELIMITERS)) != NULL) {
                    args[arg_count++] = token;
                }

                if (arg_count == 0) {
                    // If no paths are provided, default to "~"
                    hop(1, (char *[]){"~"});
                } else {
                    hop(arg_count, args);
                }
                 char cwd[4096];
        
            }
            else if (strcmp(token, "reveal") == 0) {
                // Next token is the flag or path
                int n=1024;
                char *flags[n];
                int num = 0;
                char *path = NULL;

               

                while ((token = strtok(NULL, DELIMITERS)) != NULL) {
                    if (token[0] == '-' && strlen(token) > 1) {
                        if (num < n) {
                            flags[num] = token + 1; 
                            num++;
                        } else {
                            printf("Too many flags. Ignoring flag: %s\n", token);
                        }
                    } else {
                        path = token;
                        break;
                    }
                }

                reveal(flags,num, path);
                
            }
            else if(strcmp(token, "log") == 0){
               flag=1;
                token = strtok(NULL, DELIMITERS);
                if(token==NULL){
                    
                    print_log();
                }
                else{
                    if(strcmp(token, "execute") == 0){
                        flag=1;
                        token = strtok(NULL, DELIMITERS);
                        if(token==NULL){
                            printf("Invalid command: %s\n", token);
                            flag=1;
                        }
                        else{
                        int index = atoi(token);
                        log_execute(index);
                        }

                    }
                    else if(strcmp(token, "purge") == 0){
                        flag=1;
                        log_purge();

                    }
                    else {
                         printf("Invalid command: %s\n", token);
                        flag=1;
                        
                    }
                }
            }
            else if(strcmp(token, "proclore") == 0){ 
                pid_t pid;
                token = strtok(NULL, DELIMITERS);
                if(token==NULL){
                   pid = getpid();
                }
                else {
                    pid = atoi(token);
                }
                proclore(pid);
            }
            else if(strcmp(token, "seek") == 0){ 
                 
                char *flags[4096];
                int num = 0;
                char *search=NULL;
                char *target_dir = NULL;

               

                while ((token = strtok(NULL, DELIMITERS)) != NULL) {
                    if (token[0] == '-' && strlen(token) > 1) {
                        
                        flags[num] = token + 1; 
                        num++;
                       
                    } 
                    else {
                        search = token;
                        break;
                    }
                }
                token=strtok(NULL, DELIMITERS);
                if(token!=NULL){
                target_dir = token;
                }
                seek(flags,num,search,target_dir);
                
            }
            else if (strcmp(token, "activities") == 0) {
                print_activities();
            }
             else if (strcmp(token, "ping") == 0) {
               token=strtok(NULL, DELIMITERS);
                if (token == NULL) {
                    printf("Invalid command\n");
                    return;
                }

                int pid = atoi(token);

                // Parse the signal number
                 token=strtok(NULL, DELIMITERS);
                if (token == NULL) {
                    printf("Invalid command\n");
                    return;
                }

                int signal = atoi(token);
                process_ping(pid, signal);
            }
            else if (strcmp(token, "fg") == 0) {
               token=strtok(NULL, DELIMITERS);
                if (token == NULL) {
                    printf("Invalid command\n");
                    return;
                }

                int pid = atoi(token);

             
                fg_partb(pid);
            }
            else if (strcmp(token, "bg") == 0) {
               token=strtok(NULL, DELIMITERS);
                if (token == NULL) {
                    printf("Invalid command\n");
                    return;
                }

                int pid = atoi(token);

             
                bg_partb(pid);
            }
            else if (strcmp(token, "neonate") == 0) {
               token=strtok(NULL, DELIMITERS);
                if (token == NULL||strcmp(token,"-n")!=0) {
                    printf("Invalid command\n");
                    return;
                }
                token=strtok(NULL, DELIMITERS);
                if (token == NULL) {
                    printf("Invalid command\n");
                    return;
                }


                int t = atoi(token);

             
                neonate(t);
            }
            else if (strcmp(token, "iMan") == 0) {
               token=strtok(NULL, DELIMITERS);
                if (token == NULL) {
                    printf("Invalid command\n");
                    return;
                }
                iman(token);
                while(token!=NULL){
                    
                    token=strtok(NULL, DELIMITERS);
                    continue;
                }
                
            }
            
            else {

                // Assume any other input as a system command
                and_args[and_arg_count++] = token;
                
            }
            
            token = strtok(NULL, "\t\n ");
        }
         if (and_arg_count > 0) {
           //  and_args[and_arg_count] = NULL;
          
           // and_args[and_arg_count] = NULL; // Null-terminate the arguments array
          
            if (background||redir_bgflag) {
                
                bg(and_args,and_arg_count);
                redir_bgflag = 0;
            } else {
                fg(and_args,and_arg_count);
            }
             for (int k = 0; k < and_arg_count; k++) {
                and_args[k] = NULL;
            }
            and_arg_count = 0;
           // and_arg_count = 0;
        }
    

    }
    free(cmd_parts);
    }
    free(com_array);

     if (flag==0){
       
        log_command(cmd2);
    }
   
    }


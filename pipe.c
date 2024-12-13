#include "header.h"
#include <ctype.h>
#define MAX_COMMANDS 256


void piping(char *cmdcopy)
{   
    //cmdcopy[strcspn(cmdcopy, "\n")] = '\0';
     if (cmdcopy == NULL || cmdcopy[0] == '\0') {
        fprintf(stderr, "Error: No command provided\n");
        return;
    }
    //printf("cmdcopy: %s\n", cmdcopy);
    char *p = strtok (cmdcopy, "|");
    char **pipe_args = malloc(MAX_COMMANDS * sizeof(char *));
    if (pipe_args == NULL) {
        perror("malloc");
        return;
    }

    int count = 0;

    while (p != NULL && count < MAX_COMMANDS)
    {  
        //pipe_args[count++] = trim_whitespace(p);
       // printf("p: %s\n", p);
        pipe_args[count++] = p;
        p = strtok (NULL, "|");
    }
    // Check if the number of pipes is correct
    if (count < 2) {
        fprintf(stderr, "Error: Incorrect number of pipes\n");
        free(pipe_args);
        return;
    }
    pipe_args[count] = NULL;
    pid_t p_pid;
    int pipe_arr[2];
    int fd = 0;

    for(int j=0; pipe_args[j]!=NULL; j++)
    {
        //fd of read and write end are pipe_arr[0] and pipe_arr[1], respectively.
         if (pipe(pipe_arr) == -1) {
            perror("pipe");
            break;
        }
        //fork is used before dup2: to create a new process for the command, and then set up the necessary file descriptors in that new process. This way, the redirection only affects the command being run, not the shell itself
        //if you use dup2 without fork, you're changing the file descriptors of the current process
        p_pid=fork();

        if(p_pid<0)
        {
            perror("fork");
            break;
        }
        
        else if(p_pid==0)
        {
            //duplicates the read end of the previous pipe to standard input (dup2(fd, 0)) and the write end of the current pipe to standard output (dup2(parr[1], 1))
            dup2(fd , 0);
            if(pipe_args[j+1]!=NULL){
                dup2(pipe_arr[1],1);
            }
            close(pipe_arr[0]);
            
            processinput(pipe_args[j]);
            exit(EXIT_SUCCESS);
        }
        else
        {

            wait(NULL);
            close(pipe_arr[1]);
            //sets fd to the read end of the current pipe for the next iteration.
            fd = pipe_arr[0];
        }
    }
    
    //free(pipe_args);
    
}
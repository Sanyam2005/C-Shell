#define MAX_ARGS 64
#include "header.h"
extern int flag_mhrc;
extern char *univ_home;
int checkalias(char * input)
{
    input[strlen(input)-1] = '\0';
    char cmd[4096];
    strcpy(cmd,input);
     char *p = strtok (cmd, " ");
    char **com_array = malloc(MAX_ARGS * sizeof(char *));
    int no = 0;
    while (p != NULL)
    {
        com_array[no++] = p;
        p = strtok (NULL, " ");
    }
    char path[1024];
    strcpy(path, univ_home);
    strcat(path, "/myshrc");

    FILE * file = fopen(path,"r");
    if(file == NULL)
    {
       // printf("Error in opening the file\n");
        return;
    }
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
    while((read = getline(&line,&len,file)) != -1)
    {   
        
        if(strncmp(line,"alias",5) == 0)
        {
            char *alias_name = strtok(line + 6, "="); 
            alias_name[strlen(alias_name)-1] = '\0';
           //printf("%s\n",alias_name);
            if(strcmp(alias_name,com_array[0]) == 0)
            {
                char * token = strtok(NULL,"=");
                flag_mhrc =1;
              // printf("%s\n",token);
                processinput(token);
            }
        }
        if(strncmp(line,"func",4) == 0)
        {
            char *fun_name = strtok(line+5, "(" );
            fun_name[strlen(fun_name)] = '\0';
            if(strcmp(fun_name, com_array[0]) == 0)
            {
                // read the function body line by line
                char * fun_body = (char *)malloc(1000*sizeof(char));
                strcpy(fun_body,"");
                while((read = getline(&line,&len,file)) != -1)
                {
                    if(strncmp(line,"{",1) == 0) continue;
                    if(strncmp(line,"}",1) == 0) break;

                    strcat(fun_body,line);
                }
                 
                fun_body[strlen(fun_body)-1] = '\0';
                int com_count = 0;
                char *commands[1024];
                commands[com_count++] = strtok(fun_body, "\n");
                commands[com_count++] = strtok(NULL,"\n");
                
                for(int m=0; m<com_count; m++)
                {
                    char * command = commands[m];
                    char * parts[MAX_ARGS];
                    char* s1 = strtok(command," ");
                    
                    char new_command[1024]; 
                    strcpy(new_command, s1); 
                    strcat(new_command," ");
                    if(com_array[1] == NULL){
                        printf("Invalid command\n");
                        return;
                    }
                    strcat(new_command,com_array[1]);
                    flag_mhrc = 1;
                    processinput(new_command);
                    command = strtok(NULL,";");
                }
            }
        }
    }
    fclose(file);
    return;

}
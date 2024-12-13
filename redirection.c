#include "header.h"
extern int stdout_global;

void handle_input_redirection(const char *in_file)
{
    int fd_in = open(in_file, O_RDONLY);
    if (fd_in < 0) 
    {
        perror("Input redirection");
        exit(EXIT_FAILURE);  // Fail if unable to open input file
    }
    dup2(fd_in, STDIN_FILENO);  // Redirect stdin to the input file
    close(fd_in);
}
void handle_output_redirection(const char *out_file, int outflag)
{
    int fd_out;
    if (outflag == 1)
        fd_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    else  // out_type == 2 for append
        fd_out = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd_out < 0)
    {
        perror("Output redirection");
        exit(EXIT_FAILURE);  // Fail if unable to open output file
    }
    dup2(fd_out, STDOUT_FILENO);  // Redirect stdout to the output file
    close(fd_out);
}
void redirection(char *command)
{
    int saved_stdout = dup(STDOUT_FILENO);
    int saved_stdin = dup(STDIN_FILENO);
    char *out_file = NULL;
    char *in_file = NULL;
    char *output_cmd;
    char *input_cmd;
   char* temp_outfile = NULL;
   char* temp_infile = NULL;

    //check input redirection
    char *inp_str = strstr(command, "<");
    int inflag = 0;
    
    //check output redirection  
    int outflag = 0;
    char *out = strstr(command, ">>");
    if (out != NULL) outflag = 2;
    else {
        out = strstr(command, ">");
        outflag = (out ? 1 : 0);
    }

    // Parse output redirection
    output_cmd = command;
    if (outflag!=0)
    { 
        output_cmd = strtok(command, ">");
        temp_outfile = strtok(NULL, ">");
        out_file = strtok(temp_outfile, " \t\n");
         if(out_file == NULL)
        {
            dprintf(stdout_global, "No output file found!\n");
            goto restore;
            return;
        }
    }

    // Parse input redirection
    input_cmd = output_cmd;
    if (inp_str != NULL)
    { 
        inflag = 1;
        input_cmd = strtok(input_cmd, "<");
        temp_infile = strtok(NULL, "<");
        in_file = strtok(temp_infile, " \t\n");
        
        struct stat f;
        if (stat(in_file, &f) != 0 || S_ISDIR(f.st_mode))
        {
            dprintf(stdout_global, "No input file found!\n");
            goto restore;
            return;
        }
    }

    // Handle input redirection
    if (inflag)
    {
        handle_input_redirection(in_file);
    }

    // Handle output redirection
    if (outflag)
    {
        handle_output_redirection(out_file, outflag);
    }

    // Execute the command
    processinput(input_cmd);

    // Restore the original stdin and stdout
restore:
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);
    
    dup2(saved_stdout, STDOUT_FILENO);
    close(saved_stdout);
}
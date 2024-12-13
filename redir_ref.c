// #include "header.h"

// int isfile(char* path) 
// {
//     struct stat f;
//     if (stat(path, &f) == 0 && !S_ISDIR(f.st_mode))
//         return 1;
//     else 
//         return 0;
// }

// void redirection(char *command)
// {
//     int saved_stdout = dup(STDOUT_FILENO);
//     int saved_stdin = dup(STDIN_FILENO);
    
//     char *output[2];
//     char *input[2];
//     char *out_file = NULL;
//     char *in_file = NULL;

//     // Detect input and output redirection
//     char *inp_str = strstr(command, "<");
//     int inflag = (inp_str != NULL);
    
//     int out_type = 0;
//     char *out = strstr(command, ">>");
//     if (out != NULL)
//         out_type = 2;
//     else 
//     {
//         out = strstr(command, ">");
//         if (out != NULL)
//             out_type = 1;
//     }

//     // Parse output redirection
//     output[0] = &command[0];
//     if (out_type)
//     { 
//         output[0] = strtok(command, ">");
//         output[1] = strtok(NULL, ">");
//         out_file = strtok(output[1], " \t\n");
//     }

//     // Parse input redirection
//     input[0] = output[0];
//     if (inflag)
//     { 
//         input[0] = strtok(input[0], "<");
//         input[1] = strtok(NULL, "<");
//         in_file = strtok(input[1], " \n\r\t");
//         if (!isfile(in_file))
//         {
//             fprintf(stderr, "No such input file found!\n");
//             return;
//         }
//     }

//     if (out_type && out_file == NULL)
//     {
//         fprintf(stderr, "Enter output file\n");
//         return;
//     }

//     // Handle input redirection
//     if (inflag)
//     {
//         int fd_in = open(in_file, O_RDONLY);
//         if (fd_in < 0) 
//         {
//             perror("Input redirection");
//             return;
//         }   
//         dup2(fd_in, STDIN_FILENO);  // Redirect stdin to file
//         close(fd_in);
//     }

//     // Handle output redirection
//     if (out_type)
//     {
//         int fd_out;
//         if (out_type == 1)
//             fd_out = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
//         else if (out_type == 2)
//             fd_out = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);

//         if (fd_out < 0)
//         {
//             perror("Output redirection");
//             return;
//         }
//         dup2(fd_out, STDOUT_FILENO);  // Redirect stdout to file
//         close(fd_out);
//     }

//     // Execute the command
//     processinput(input[0]);

//     // Restore the original stdin and stdout
//     dup2(saved_stdin, STDIN_FILENO);
//     close(saved_stdin);
    
//     dup2(saved_stdout, STDOUT_FILENO);
//     close(saved_stdout);
// }

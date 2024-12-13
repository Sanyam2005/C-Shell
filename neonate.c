#include "header.h"
#include <termios.h>

struct termios cooked;

void check(int result, const char* action) {
    if (result < 0) {
        perror(action);
        exit(EXIT_FAILURE);
    }
}
void disableRawMode() {
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &cooked) == -1){
        perror("tcsetattr");
        exit(EXIT_FAILURE);
    }
}


void neonate(int time_arg) {

    if (time_arg <= 0) {
        fprintf(stderr, "Invalid time argument. Must be a positive integer.\n");
        return EXIT_FAILURE;
    }
    //disable buffering: output written to stdout will be written immediately, instead of being buffered and written all at once when the buffer is full or when the stream is flushed or closed.
    setbuf(stdout, NULL);
    //enable raw mode
    //retrieves the current terminal settings and stores them in the cooked structure
    if (tcgetattr(STDIN_FILENO, &cooked) == -1){
        perror("tcgetattr");
        exit(1);
    }
    //restore the terminal settings when the program exits
    atexit(disableRawMode);
    //modifies the raw structure to disable canonical mode and echo. Canonical mode is what allows the terminal to process input line-by-line. Echo is what causes the terminal to print out every character you type. Disabling these features puts the terminal into raw mode, where input is processed character-by-character and not automatically printed to the screen.
    struct termios raw = cooked;
    raw.c_lflag &= ~(ICANON | ECHO);
    //APPLIES THE MODIFIED SETTINGS TO THE TERMINAL
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw) == -1){
        perror("tcsetattr");
        exit(1);
    } 
    
    //fork a child process
    pid_t pid = fork();
    if (pid < 0) {
        perror("fork");
        exit(EXIT_FAILURE);
    } 
    
    else if (pid == 0) {
        // Child process: Periodically print the most recent PID
        while (1) {

            //This file contains the PID of the most recently created process.
            FILE *f = fopen("/proc/sys/kernel/ns_last_pid", "r");
            if (f == NULL) {
                perror("fopen");
                exit(EXIT_FAILURE);
            }
            
            char last_pid[10];
            fgets(last_pid, sizeof(last_pid), f);
            printf("Last PID: %s", last_pid);

            fclose(f);
            sleep(time_arg);  // Wait for the specified time interval
        }
    } 
    else {
        // Parent process: Listen for 'x' or 'X' keypress to terminate
        char input;
        while (read(STDIN_FILENO, &input, 1) == 1) {
            if (input == 'x') {
                kill(pid, SIGKILL);  // Kill the child process
                break;
            }
        }
    }
     disableRawMode();
}

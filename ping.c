#include "header.h"

void process_ping(int pid, int signal) {
    
     int mod_signal = signal % 32;

    // If the process with the given pid exists, kill returns 0. If the process does not exist, kill returns -1 and sets errno to ESRCH
    if (kill(pid, 0) == -1) {
        if (errno == ESRCH) {
            printf("No such process found\n");
            return;
        }
        perror("Error checking process");
        return;
    }

    // Send the signal
    if (kill(pid, mod_signal) == -1) {
        perror("Failed to send signal");
    } else {
        printf("Sent signal %d to process with pid %d\n", mod_signal, pid);
        
    }
}

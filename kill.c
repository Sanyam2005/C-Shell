#include "header.h"

extern int p_count;
extern process_act p_list[1024];

void handle_ctrl_d() {
    for(int i=0; i < p_count; i++)
        kill(p_list[i].pid, 9);
    exit(0); // Exit the shell
}
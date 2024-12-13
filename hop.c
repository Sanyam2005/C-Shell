// // hop.c

#include "header.h"
#include "hop.h"
extern char *univ_home;
extern char *prevdir;

 void hop(int argc, char **argv) {
    for (int i = 0; i < argc; i++) {
        char *path = argv[i];
        char *newpath = NULL;

        if (strcmp(path, "~") == 0) {
            newpath = univ_home;
        }
        else if (strcmp(path, "-") == 0) {
            newpath = prevdir;
        } 
        else {
            newpath = path;
        }

        if (access(newpath, F_OK) != 0) {
            perror(newpath);
            continue;
        }

        char *olddir = getcwd(NULL, 0);
        if (chdir(newpath) != 0) {
            perror(newpath);
            free(olddir);
            continue;
        }

        char cwd[4096];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Current working directory: %s\n", cwd);
        } else {
            perror("getcwd failed");
        }

        prevdir = olddir;
    }
}
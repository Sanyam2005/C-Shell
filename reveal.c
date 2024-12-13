#include "header.h"
#include "reveal.h"
#include <dirent.h> 
#include <pwd.h>
#include <grp.h>
#include <time.h>                               
#define RESET_COLOR "\x1b[0m"
#define GREEN_COLOR "\x1b[32m"
#define WHITE_COLOR "\x1b[37m"
#define BLUE_COLOR "\x1b[34m"
extern char *univ_home;
extern char *prevdir;
extern int stdout_global;
char *getPermissions(mode_t mode) {
    static char permissions[11];

    permissions[0] = S_ISDIR(mode) ? 'd' : '-';
    permissions[1] = mode & S_IRUSR ? 'r' : '-';
    permissions[2] = mode & S_IWUSR ? 'w' : '-';
    permissions[3] = mode & S_IXUSR ? 'x' : '-';
    permissions[4] = mode & S_IRGRP ? 'r' : '-';
    permissions[5] = mode & S_IWGRP ? 'w' : '-';
    permissions[6] = mode & S_IXGRP ? 'x' : '-';
    permissions[7] = mode & S_IROTH ? 'r' : '-';
    permissions[8] = mode & S_IWOTH ? 'w' : '-';
    permissions[9] = mode & S_IXOTH ? 'x' : '-';
    permissions[10] = '\0';

    return permissions;
}

int compare(const struct dirent **a, const struct dirent **b) {
    return strcasecmp((*a)->d_name, (*b)->d_name);
}

void reveal(char **flags,int n, char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat fileStat;
    struct dirent **namelist;
    int a_flag = 0;
    int l_flag = 0;
    int count=0;

    if (path == NULL) {
        path = ".";
    }
    
    
    if (path[0] == '~') {
        path = univ_home;
        }
    // Expand "-" to the previous directory
    else if (path[0] == '-') {
        if(prevdir!=NULL){
            path = prevdir;
        }
        else{
            dprintf(stdout_global,"No previous directory found\n");
            return;
        }
    }
    if (flags != NULL) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; flags[i][j] != '\0'; j++) {
                if (flags[i][j] == 'l') {
                    l_flag = 1;
                }
                else if (flags[i][j] == 'a') {
                    a_flag = 1;
                }
            }
        }
    }
    if (stat(path, &fileStat) == -1) {
        perror(path);
        return;
    }
    //check if the path is a directory
    if (S_ISDIR(fileStat.st_mode)) {
    dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        return;
    }

     count = scandir(path, &namelist, NULL, compare);
        if (count < 0) {
            perror("scandir");
            closedir(dir);
            return;
        }
    //calcutate the total x number of blocks
    long total_blocks = 0;
    if (l_flag) {
        while ((entry = readdir(dir)) != NULL) {
            if (a_flag || entry->d_name[0] != '.') {
                char filepath[4096];
                snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);
                if (stat(filepath, &fileStat) == -1) {
                    perror(entry->d_name);
                    continue;
                }
                total_blocks += fileStat.st_blocks;
            }
        }

        dprintf(stdout_global,"total %ld\n", total_blocks/2);

        // Reset the directory stream to the beginning
        rewinddir(dir);
    }
    //The function reads the entries in the directory one by one using readdir. readdir returns NULL when there are no more entries in the directory.
    for (int i = 0; i < count; i++) {
            struct dirent *entry = namelist[i];

        //For each entry, the function checks whether it's a hidden file (i.e., its name starts with a dot). If the show_all flag is not set and the entry is a hidden file, the function skips to the next entry.
        if (a_flag==0 && entry->d_name[0] == '.') {
            entry = readdir(dir);
            continue;
        }

        char filepath[4096];
        snprintf(filepath, sizeof(filepath), "%s/%s", path, entry->d_name);
        //stat fills a struct stat with information about the file or directory, such as its size and the time of its last modification. If stat returns a negative value, it means an error occurred.
        if (stat(filepath, &fileStat) < 0) {
            perror("stat");
            continue;
        }

        char *color;
        //The function checks the file type of the entry. If the entry is a directory, the function sets the color to blue. If the entry is an executable file, the function sets the color to green. Otherwise, the function sets the color to white.
        if (S_ISDIR(fileStat.st_mode)) {
            color = BLUE_COLOR;
        } 
        //S_IXUSR is a mask for the user execute permission bit. The & operator performs a bitwise AND operation between fileStat.st_mode and S_IXUSR
        else if (fileStat.st_mode & S_IXUSR) {
            color = GREEN_COLOR;
        } 
        else {
            color = WHITE_COLOR;
        }
        //t prints the name of the file or directory (entry->d_name), its size (fileStat.st_size), and the user ID (fileStat.st_uid) and group ID (fileStat.st_gid) of its owner
        if (l_flag) {
            struct passwd *pw = getpwuid(fileStat.st_uid);
            struct group  *gr = getgrgid(fileStat.st_gid);
            char timebuf[80];
            strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&fileStat.st_mtime));
            dprintf(stdout_global,"%s%10.10s %ld %s %s %5ld %s %s%s\n", color, getPermissions(fileStat.st_mode), fileStat.st_nlink, pw->pw_name, gr->gr_name, fileStat.st_size, timebuf, entry->d_name, RESET_COLOR);
            } 
            else {
                dprintf(stdout_global,"%s%s%s\n", color, entry->d_name, RESET_COLOR);
            }
        
        entry = readdir(dir);
    }
     
    for (int i = 0; i < count; i++) {
        free(namelist[i]);
    }
    free(namelist);
    closedir(dir);
    }
    //if it is a file,just print its details
     else {
        if (l_flag) {
            struct passwd *pw = getpwuid(fileStat.st_uid);
            struct group  *gr = getgrgid(fileStat.st_gid);
            char timebuf[80];
            strftime(timebuf, sizeof(timebuf), "%b %d %H:%M", localtime(&fileStat.st_mtime));

            dprintf(stdout_global,"%10.10s %ld %s %s %5ld %s %s\n", 
                getPermissions(fileStat.st_mode), 
                fileStat.st_nlink, 
                pw->pw_name, 
                gr->gr_name, 
                fileStat.st_size, 
                timebuf, 
                path);
        } else {
            dprintf(stdout_global,"%s\n", path);
        }
    }
}
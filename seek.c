#include "header.h"
#include "reveal.h"
#include <stdbool.h>                 
#define RESET_COLOR "\x1b[0m"
#define GREEN_COLOR "\x1b[32m"
#define WHITE_COLOR "\x1b[37m"
#define BLUE_COLOR "\x1b[34m"
#define COLOR_GREEN "\033[32m"
#define COLOR_BLUE "\033[34m"
#define COLOR_RESET "\033[0m"

extern char *univ_home;
extern char *prevdir;
#define MAX_RESULTS 4096

void search_directory(const char *base_path,const char* rel_path, const char *search, int f_d, int f_f, int f_e, char *results[],char *final_results[], int *count) ;

void seek(char **flags,int n, char *search, char * path) {
    
    int d_flag = 0;
    int f_flag = 0;
    int e_flag=0;
    //results stores the relative path while final_results stores the absolute path wrt home
    char *results[4096];
    char *final_results[4096];
    int count = 0;
    
    
    if (path == NULL) {
        path = ".";
    }
    
    if (path[0]=='~')  {
        path = univ_home;
    }
    
    else if (path[0] == '-') {
        if(prevdir!=NULL){
            path = prevdir;
        }
        else{
            printf("No previous directory found\n");
            return;
        }
    }
    if (flags != NULL) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; flags[i][j] != '\0'; j++) {
                if (flags[i][j] == 'e') {
                    e_flag = 1;
                }
                else if (flags[i][j] == 'd') {
                    d_flag = 1;
                }
                 else if (flags[i][j] == 'f') {
                    f_flag = 1;
                }
            }
        }
    }
    if(f_flag==1 && d_flag==1){
        printf("Invalid flags\n");
        return;
    }
    if(search == NULL){
        printf("No search term provided\n");
        return;
    }
    printf("Searching for %s in %s\n", search, path);
    //define a relative path and search recursively
    char rel_path[4096] = ".";
    search_directory(path,rel_path, search, d_flag, f_flag, e_flag, results,final_results, &count);
    if (count == 0) {
        printf("No match found!\n");
    } 
    else {
        //print according to the color coding
         for (int i = 0; i < count; i++) {
            struct stat st;
            stat(final_results[i], &st);
            if (S_ISDIR(st.st_mode)) {
                printf(COLOR_BLUE "%s" COLOR_RESET "\n", results[i]);
            } else if (S_ISREG(st.st_mode)) {
                printf(COLOR_GREEN "%s" COLOR_RESET "\n", results[i]);
            }
           
        }
    }
    //if e flag is set then print the contents of the file or hop to directory if only one file/directory is found
  if (e_flag && count == 1) {
        struct stat st;
        stat(final_results[0], &st);
        if (S_ISREG(st.st_mode)) {
            FILE *fp = fopen(final_results[0], "r");
            if (fp) {
               char line[4096];
                while (fgets(line, sizeof(line), fp) != NULL) {
                    printf("%s", line);
                }
                fclose(fp);
                printf("\n");
            } 
            else {
                printf("Missing permissions for task!\n");
            }
        } 
        else if (S_ISDIR(st.st_mode)) {
            if (chdir(final_results[0]) == 0) {
                //printf("%s/\n", final_results[0]);
            } 
            else {
                printf("Missing permissions for task!\n");
            }
        }
    }
    //free the memory
    for (int i = 0; i < count; i++) {
            free(final_results[i]);
            free(results[i]);
    }
    
}

void search_directory(const char *base_path,const char* rel_path, const char *search, int f_d, int f_f, int f_e, char *results[],char *final_results[], int *count) {
    DIR *dp;
    struct dirent *entry;
    char full_path[4096];
    char newrel_path[4096];
    dp = opendir(base_path);
   
    if (dp == NULL) {
        //  printf("%s\n",base_path);
        return;
    }

    while ((entry = readdir(dp)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        snprintf(full_path, sizeof(full_path), "%s/%s", base_path, entry->d_name);
        snprintf(newrel_path, sizeof(newrel_path), "%s/%s", rel_path, entry->d_name);
        struct stat st;
        stat(full_path, &st);

        int is_dir = S_ISDIR(st.st_mode);
        int is_file = S_ISREG(st.st_mode);

        // Check if the entry's name begins with the search string.Also check if it correct entry according to the flags
        bool match = (f_d==1 && is_dir==1) || (f_f==1 && is_file==1) || (f_d==0 && f_f==0);
        if (strncmp(entry->d_name, search, strlen(search)) == 0) {
            if (match && *count < MAX_RESULTS) {
               
                final_results[(*count)] = strdup(full_path);
                results[(*count)] = strdup(newrel_path);
                (*count)++;
            }
        }
        //call function recursively if it is a directory
        if (is_dir) {
            search_directory(full_path,newrel_path, search, f_d, f_f, f_e, results,final_results, count);
        }
    }
    closedir(dp);
}
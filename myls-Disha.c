/*List Files: This application displays all of the files in a specified directory. If you call this function without any arguments, 
it will just print out all of the file names.
The program writes out information about each file when the -l flag is used.*/

#include <stdio.h>     // for perror
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>    // for getopt
#include <stdlib.h>    // for exit
#include <dirent.h>    // for opendir, readdir, and closedir
#include <string.h>    
#include <stdbool.h>
#include <time.h>      // for localtime

int main(int argc, char *argv[]) {
    struct stat sta;
    int opt;
    char * path = ".";
    struct dirent *d;
    bool lists = false;
    DIR *dp;
    opterr = 0;    

    while ((opt = getopt(argc, argv, "l:")) != -1) {
        if(opt == 'l' ){
            path = optarg;
            lists = true;
        }
        else if(opt == '?'){
            if (optopt == 'l')
                lists = true;   
        }
        else{
            break;
        }

    }

    if (stat(path, &sta) == -1)
        do { perror("stat"); exit(EXIT_FAILURE); } while (0);

    if (argc > 1 && !lists)
        path = argv[1];
    
    // need exactly two arguments
    if(argc > 3){
        printf("Invalid format.\n");
        return 0;
    }
    
    if (S_ISDIR(sta.st_mode)) {
        if ((dp = opendir(path)) == NULL)
            do { perror("opendir"); exit(EXIT_FAILURE); } while (0);
        while ((d = readdir(dp)) != NULL) {
            if (lists) {
                char filePath[1024] = "";
                strncpy(filePath, path, strlen(path));
                strncat(filePath, "/", 1);
                strncat(filePath, d->d_name, strlen(d->d_name));
                if (stat(filePath, &sta) == -1)
                    do { perror("stat"); exit(EXIT_FAILURE); } while (0);
                print_file(sta);
            }
            printf("%s\n", d->d_name);
        }
        closedir(dp);
    } else {
        if (lists)
            print_file(sta);
        printf("%s\n", path);
    }
    exit(EXIT_SUCCESS);
}

void print_file(struct stat sta) {
    printf("%4lo  ", (unsigned long) sta.st_mode);
    printf("%3ld  ", (long) sta.st_nlink);
    printf("%3ld  ", (long) sta.st_uid);
    printf("%3ld  ", (long) sta.st_gid);
    printf("%4lld  ", (long long) sta.st_size);
    char timeStr[1024] = "";
    strftime(timeStr, 1024, "%b %d %H:%M", localtime(&sta.st_mtime));
    printf("%s  ", timeStr);
}
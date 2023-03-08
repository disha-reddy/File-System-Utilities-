/*  Stat- Create a command-line program stat that executes the stat() system call on a specific file or directory. 
The file size, total size in bytes, number of allocated blocks, reference count, file premissions, and file inode number are all obtained.
*/
#include <stdlib.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>

typedef struct dirent Dir;
typedef struct stat Info;

Info getDirInfo(char * dir)
{
        Info info;
        stat(dir, &info);
        return info;
}

int main(int argc, char *argv[]){
    
    DIR * root=opendir(".");
    Dir * dir=readdir(root);
    for(; dir!= NULL; dir=readdir(root)){

        printf("Name: %s\t\t\t",dir->d_name);
        Info info= getDirInfo(dir->d_name);
        printf("File Size: %lld Bytes\n",info.st_size);
        //printf("Number of blocks allocated: %lld Blocks\n", info.st_blocks);
        printf("Number of Links: %ho\n",info.st_nlink);
        
        printf("File Permissions: ");
        //if we are passing directory
        if (S_ISDIR(info.st_mode)){
            printf("d");
        }
        else {
        printf("-");
        }
        // read permission
        if (info.st_mode & S_IRUSR){
            printf("r");
        }
        else{
            printf("-");
        }
        // write permission
        if (S_IWUSR & info.st_mode) {
            printf("w");
        }
        else{   
            printf("-");
        }
        // execute permission
        if (info.st_mode & S_IXUSR){
            printf("x");
        }
        else{
            printf("-");
        }

        if (info.st_mode & S_IRGRP) {
            printf("r"); 
        }

        else {
            printf("-");
        }

        if (info.st_mode & S_IWGRP){
            printf("w");
        }
        else {
            printf("-");
        }

        if (info.st_mode & S_IXGRP){
            printf("x"); 
        }
        else{
            printf("-");
        }

        if (info.st_mode & S_IROTH){
            printf("r"); 
        }
        else{
            printf("-");
        }

        if (info.st_mode & S_IWOTH){
            printf("w"); 
        }
        else{
            printf("-");
        }

        if (info.st_mode & S_IXOTH){
            printf("x"); 
        }
        else{
            printf("-");
        }
        printf("\n\n");
        printf("File Inode number: %lld\n",info.st_ino);
    }
    closedir(root);
    return 0;

}
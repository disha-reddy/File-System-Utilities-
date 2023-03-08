/* Recursive Search: When no other arguments are specified, this program prints the names of each file and the directory, 
as well as the contents of each file.
*/

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>   
#include <dirent.h>  
#include <string.h>  
#include <stdio.h>

void search(char *name){
  DIR *d;
  d = opendir(name);
  struct stat dirstat;
  char path[10000];
  struct dirent *dirStr;

  
  dirStr = readdir(d);
  //checking for files
  while (dirStr != NULL){
    //i finding . and ..
    if (strcmp(dirStr->d_name, ".") != 0 && strcmp(dirStr->d_name, "..") != 0){ 
      printf("Filename: ");
      printf("%s\n", dirStr->d_name);
      stat(dirStr->d_name,&dirstat);
      if (S_ISDIR(dirstat.st_mode)){  
        strcpy(path, name);
        strcat(path, "/");
        strcat(path, dirStr->d_name);
        printf("%sdirect:\n", path);
        search(path);
      }
    }
    dirStr = readdir(d); 
  }
  closedir(d);
  printf("%s\n", name);
}

int main(int argc, char **argv){
  DIR *d;
  char *name;

  if (argc > 1){
    name = argv[1];
  }  else {
    name = ".";
  }

  search(name);
}
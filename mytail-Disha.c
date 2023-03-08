/* Tail: Create a program that prints the file's last few lines. The software should be efficient in that it searches for the file's end, 
reads a block of data, and then searches backwards until it finds the desired amount of lines. 
Those lines should be printed from the beginning to the end of the file.
*/
#include <stdio.h>     
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>    
#include <stdlib.h>    
#include <fcntl.h>     
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 3 || strlen(argv[1]) <= 1 || argv[1][0] != '-') {
        printf("Invalid format.\n After the executable, should enter exactly two argument : \n.offset filename\n");
        return 0;
    }

    struct stat sta;
    int f;
    int offset; 
    int l;
    char * path = "";

    l = atoi(argv[1]);
    l *= -1;
    l++;
    path = argv[2];

    if ((f = open(path, O_RDONLY)) == -1)
        do { perror("open"); return 0; } while (0);

    if (stat(path, &sta) == -1)
        do { perror("stat"); return 0; } while (0);

    if (lseek(f, -1, SEEK_END) == -1)
        do { perror("lseek"); return 0; } while (0);

    char buff[sta.st_size];
    while (l > 0) {
        if (buff[0] == '\n')
            l--;

        if (read(f, buff, 1) == -1)
            do { perror("read"); return 0; } while (0);
        
        offset = lseek(f, -2, SEEK_CUR);
        if (offset == -1)
            break;
    }

    memset(buff, 0, sta.st_size);
    if (read(f, buff, sta.st_size) == -1)
        do { perror("read"); return 0; } while (0);

    printf("%s", buff);
    close(f);

    return 0;
}
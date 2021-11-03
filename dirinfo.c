#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <dirent.h>
#include <sys/types.h>
#include <time.h>

/* For the current directory ("./")
list all the files in the directory
specify which files are directories (if any)
show the total size of all the regular files the directory
note that you do not have to recursively go through any subdirectories to find their size for this part (unless you want to, but that is not a simple task)
Possible enhancements:
Recursively list the files in any subdirectories, update the total to include the total size of subdirectories
Print out the size in a more readable format (like using KB, MB, GB for -byte prefixes)
Make it look more like $ ls -l
*/

int octal(int a) {
    int output = 0;
    int digit = 1;
    while (a > 0) {
        output = output + (a % 8) * digit;
        a /= 8;
        digit *= 10;
    }
    return output;
}

char* octaltoperm(int a) {
    if (a == 7)
        return "rwx";
    else if (a == 6)
        return "rw-";
    else if (a == 5)
        return "r-x";
    else if (a == 4)
        return "r--";
    else if (a == 3)
        return "-wx";
    else if (a == 2)
        return "-w-";
    else if (a == 1)
        return "--x";
    else return "---";
}

void printperm(int a) {
    int o;
    int g;
    int ot;
    o = a % 1000 / 100;
    g = a % 100 / 10;
    ot = a % 10;
    printf("%s%s%s\t", octaltoperm(o),octaltoperm(g),octaltoperm(ot));
    
    
}



int main() {

    DIR *current = opendir("./");
    if (current == NULL) printf("Failed");
    struct dirent *entry;
    struct stat s;
    
    entry = readdir(current);

    /* testing stat
    stat("123", &s);
    printf("%d", (&s) -> st_mode); */

    int sum = 0;
    int perm;
    while (entry) {
        if (entry -> d_type == 4) {
            printf("d");
        }
        else if (entry -> d_type == 8) {
            printf("-");
            stat(entry->d_name, &s);
            sum += (&s) -> st_size;
        }

        stat(entry->d_name, &s);
        perm = octal( (&s) -> st_mode);
        printperm(perm);

        if (entry -> d_type == 8)
            printf("%ld", (&s) -> st_size);
        printf(" \t%s\n", entry->d_name);


        entry = readdir(current);
    }
    if (sum > 1000)
        printf("Total Directory Size: %d KB", sum / 1000);
    else if (sum > 1000000)
        printf("Total Directory Size: %d KB", sum / 1000000);
    else if (sum > 1000000000)
        printf("Total Directory Size: %d KB", sum / 1000000000);
    else
        printf("Total Directory Size: %d Bytes", sum);
    printf("\n");


    closedir(current);
}
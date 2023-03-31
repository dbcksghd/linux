#include <sys/types.h>
#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    DIR *dirp;
    char buffer[1024];
    int nread, count = 0, dirCount = 0;
    struct dirent *dentry;

    if ((dirp = opendir(argv[1])) == NULL) exit(1);
    nread = readlink(argv[1], buffer, 1024);
    while ((dentry = readdir(dirp))) {
        if (dentry->d_ino != 0) count++;
        if (opendir(dentry->d_name) != NULL) dirCount++;
    }

    printf("%d %d\n", count, dirCount);
    if (nread == -1)  printf("%s is not soft-link\n", argv[1]);
    else printf("%s is soft-link!\n", argv[1]);
    closedir(dirp);
}

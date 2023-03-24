#include <stdio.h>
#include <unistd.h>

int main(int agrc, char **argv){
    if (symlink(argv[1], argv[2])) printf("soft-link failed\n");
}

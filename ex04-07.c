#include <stdio.h>
#include <unistd.h>

int main(int agrc, char **argv){
    if (link(argv[1], argv[2])) printf("hard-link failed\n");
}

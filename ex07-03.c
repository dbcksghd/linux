#include <unistd.h>
#include <stdio.h>

int main() {
    printf("before \n");
    execl("/bis/ls", "ls", "-l", (char *) 0);
    printf("after \n");

    return 0;
}

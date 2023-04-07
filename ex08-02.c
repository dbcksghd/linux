#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status = 0;
    pid = fork();
    if (pid > 0) {
        printf("parent: waiting..\n");
        wait(&status);

        printf("parent: status is %d\n", status);
    } else if (pid == 0) {
        sleep(1);
        printf("child: bye!\n");
        exit(1);
    } else
        printf("fail to fork\n");
    printf("bye!\n");
}

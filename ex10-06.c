#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdio.h>

int main() {
    pid_t pid;
    int count = 5;
    if ((pid = fork()) > 0) {
        sleep(2);
        kill(pid, SIGINT);
        raise(SIGINT);
        printf("부모로부터 떨어짐");
    } else if (pid == 0) {
        while (count) {
            printf("child count is %d\n", count--);
            sleep(1);
        }
    } else printf("fail to fork\n");
}

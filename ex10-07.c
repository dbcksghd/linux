#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void timeOver(int signum) {
    printf("\n\ntime over!!\n\n");
    exit(0);
}

int main() {
    char buf[1024];
    char *alpha = "abcdefghijklmnopqrstuvwxyz";
    int timeLimit;
    struct sigaction act;

    act.sa_handler = timeOver;
    sigaction(SIGALRM, &act, NULL);
    printf("input timeLimit (sec)..\n");
    scanf("%d", &timeLimit);

    alarm(timeLimit);

    printf("START!!\n > ");
    scanf("%s", buf);

    if (!strcmp(buf, alpha))printf("well done.. you succeed!\n");
    else printf("sorry.. you fail!\n");
}

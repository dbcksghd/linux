#include <unistd.h>
#include <stdio.h>

int main(){
    pid_t pid;
    int i = 0;
    i++;
    printf("before colling fork(%d)\n", i);
    
    pid = fork();
    if (pid == 0){
        printf("child process(%d)\n", ++i);
    } else if (pid > 0){
        printf("parent process(%d)\n", --i);
    } else {
        printf("fail to fork\n");
    }
}

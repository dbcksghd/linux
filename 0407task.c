
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    int n;
    scanf("%d", &n);

    pid_t pid;
    pid = fork();

    if (pid > 0) {
        int sum = 0;
        for (int i = 1; i <= n; i++) {
            sum += i;
        }
        printf("합 : %d\n", sum);
    } else {
        int sum = 1;
        for (int i = 1; i <= n; i++) {
            sum *= i;
        }
        printf("곱 : %d\n", sum);
    }
}

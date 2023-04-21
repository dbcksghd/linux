#include <unistd.h>

int main(int agrc, char *argv[]) {
    for (int i = 1; i < agrc; i++) {
        int f = fork();
        if (f == 0) {
            char *a[] = {"wc", argv[i], (char *) 0};
            execvp("wc", a);
        }
    }
}


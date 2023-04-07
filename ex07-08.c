#include <stdlib.h>
#include <stdio.h>

void func1(void) {
    printf("func1\n");
}

void func2(void) {
    printf("func2\n");
}

int main() {
    printf("hello!\n");
    atexit(func1);
    atexit(func2);

    printf("bye!\n");
    exit(0);
}

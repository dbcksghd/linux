#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    if (access("./b.txt", F_OK) == -1) {
        fprintf(stderr, "User cannot find file b.txt \n");
        exit(1);
    }

}

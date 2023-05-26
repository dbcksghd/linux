#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define SIZE 512

int main() {
    char *msg1 = "apple is red";
    char *msg2 = "banana is yellow";
    char buffer[SIZE];

    int fileDes[2];
    int nRead;

    if (pipe(fileDes) == -1) {
        printf("fail to call pipe()\n");
        exit(1);
    }
    write(fileDes[1], msg1, SIZE);
    write(fileDes[1], msg2, SIZE);

    nRead = read(fileDes[0], buffer, SIZE);
    printf("%d %s\n", nRead, buffer);


    nRead = read(fileDes[0], buffer, SIZE);
    printf("%d %s\n", nRead, buffer);
}

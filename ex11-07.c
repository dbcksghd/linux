#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define SIZE 512

int main() {
    char *msg1 = "apple is red";
    char *msg2 = "banana is yellow";
    char buffer[SIZE];

    int fileDes[2];
    int nRead;

    int len1 = strlen(msg1) + 1;
    int len2 = strlen(msg2) + 1;

    if (pipe(fileDes) == -1) {
        printf("fail to call pipe()\n");
        exit(1);
    }
    write(fileDes[1], msg1, len1);
    write(fileDes[1], msg2, len2);

    nRead = read(fileDes[0], buffer, len1);
    printf("%d %s\n", nRead, buffer);


    nRead = read(fileDes[0], buffer, len2);
    printf("%d %s\n", nRead, buffer);
}

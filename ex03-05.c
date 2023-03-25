#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>

int main(){
    int filedes;
    off_t newpos;
    
    filedes = open("data1.txt", O_RDONLY);
    
    newpos = lseek(filedes, (off_t)0, SEEK_END);
    printf("file size : %ld\n", newpos);
}

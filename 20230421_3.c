#include <unistd.h>
#include <stdlib.h>
int main() {
	setenv("MYDATA","5",0);
	execl("./20230421_3-1","20230421_3-1", (char *)0); 
}


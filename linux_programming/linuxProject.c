#include "linuxProject.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int status;
    char exit_code[50];

    swManager *mySwInfo = (swManager *) malloc(sizeof(swManager));
    InitSwManager(mySwInfo);

    readFileList(mySwInfo);
    InitSWBlock(mySwInfo);

    while (1) {
        mySwInfo->dpid = waitpid(-1, &status, 0);

        if (mySwInfo->dpid != -1) {
            int idx = FindIndex(mySwInfo);
            mySwInfo->sw_info[idx].int_restart++;
            sprintf(mySwInfo->sw_info[idx].restart_count, "%d", mySwInfo->sw_info[idx].int_restart);

            if (WIFEXITED(status)) {
                sprintf(exit_code, "EXIT(%d)", WEXITSTATUS(status));
                strcpy(mySwInfo->sw_info[idx].reason, exit_code);
            } else if (WIFSIGNALED(status)) {
                sprintf(exit_code, "SIGNAL(%d).%s", WTERMSIG(status), strsignal(WTERMSIG(status)));
                strcpy(mySwInfo->sw_info[idx].reason, exit_code);
            }

            restartProcess(mySwInfo, idx);
            LogWrite(&(mySwInfo->sw_info[idx]));
            LogInterface(mySwInfo);
        }
    }
}
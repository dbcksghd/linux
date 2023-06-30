#include "linuxProject.h"
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main() {
    int status;
    char exit_code[50];
    mkdir(LOGDIR, 0755);
    FILE *log_file = fopen(LOGDIR LOGFILE, "a");
    static swManager mySwInfo;
    InitSwManager(&mySwInfo); // swManager 초기화
    readFileList(&mySwInfo); // FileList 파일로부터 정보를 읽어옴
    InitSwBlock(&mySwInfo, log_file); // swBlock 초기화
    while (1) {
        mySwInfo.dpid = waitpid(-1, &status, 0); // waitpid로 감시
        if (mySwInfo.dpid != -1) { // 뭔가 잘못됐을 경우
            int idx = FindIndex(&mySwInfo); // dpid와 같은 pid의 인덱스를 반환
            mySwInfo.sw_info[idx].int_restart++; // restart count 증가
            sprintf(mySwInfo.sw_info[idx].restart_count, "%d",
                    mySwInfo.sw_info[idx].int_restart);
            if (WIFEXITED(status)) { // 자식이 정상적으로 종료되었을 때
                sprintf(exit_code, "EXIT(%d)", WEXITSTATUS(status));
                strcpy(mySwInfo.sw_info[idx].reason, exit_code);
            } else if (WIFSIGNALED(status)) { // 자식이 시그널로 종료되었을 때
                sprintf(exit_code, "SIGNAL(%d).%s", WTERMSIG(status),
                        strsignal(WTERMSIG(status)));
                strcpy(mySwInfo.sw_info[idx].reason, exit_code);
            }
            restartProcess(&mySwInfo, idx); // 프로세스를 재시작해주고 시작시간 갱신
            LogWrite(log_file, &mySwInfo.sw_info[idx]); // 로그 기록
            LogInterface(&mySwInfo); // 콘솔창에 출력
        }
    }
    fclose(log_file);
}
#ifndef __LINUX_PROJECT_H__
#define __LINUX_PROJECT_H__

#include <sys/types.h>

#define MAX_STR 100
#define BLOCK_COUNT 10

#define LOGDIR  "./log"
#define LOGFILE "restart.txt"


typedef struct _swInfo {
    char name[20]; //프로세스 이름
    char restart_count[20]; //재시작 횟수 (char*)
    char start_time[30]; //시작/재시작  시간
    char reason[50]; //종료 이유
    int int_restart; //재시작 횟수 (int)
} swInfo;

typedef struct _swParam {
    char SwBlock[20]; // 프로세스 이름
    char App_params[3][20]; //파라미터
} swParam;

typedef struct _swInfoManager {
    pid_t pids[BLOCK_COUNT]; //pid 배열
    pid_t dpid; //죽은 pid
    int p_no; //pid 숫자
    swInfo sw_info[BLOCK_COUNT]; // swInfo 구조체 배열
    swParam sw_param[BLOCK_COUNT]; // swParam 구조체 배열
} swManager;

void InitSwManager(swManager *info);

void readFileList(swManager *info);

void InitSwBlock(swManager *info, FILE *log_file);

void restartProcess(swManager *info, int index);

void LogInterface(const swManager *info);

int FindIndex(const swManager *info);

char *rtrim(const char *s);

char *ltrim(const char *s);

char *trim(const char *s);

char *getTime(void);

void LogWrite(FILE *log_file, const swInfo *list);

#endif
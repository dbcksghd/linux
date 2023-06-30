#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "linuxProject.h"

void InitSwManager(swManager *info) {
    memset(info, 0, sizeof(*info));
}

void readFileList(swManager *info) {
    char str[MAX_STR];
    int swno = 0;
    swParam *param = info->sw_param;
    FILE *fp = fopen("./FileList", "r");
    while (fgets(str, MAX_STR, fp)) {
        String result;
        str[strlen(str) - 1] = 0;
        result = trim(strtok(str, ";"));
        strcpy(param[swno].SwBlock, result);
        free(result);
        for (int i = 0; i < 3 && (result = strtok((char *) 0, ";"));
             i++) {
            result = trim(result);
            strcpy(param[swno].App_params[i], result);
            free(result);
        }
        swno++;
    }
    info->p_no = swno;
}

void InitSwBlock(swManager *info, FILE *log_file) {
    pid_t pid;
    int i, status;
    swInfo *sw_info = info->sw_info;
    for (i = 0; i < info->p_no; i++) {
        strcpy(sw_info[i].name, info->sw_param[i].SwBlock);
        sprintf(sw_info[i].reason, "Init.");
        sprintf(sw_info[i].restart_count, "%d", 0);
        strcpy(sw_info[i].start_time, getTime());
        if (log_file)
            LogWrite(log_file, &info->sw_info[i]);
        LogInterface(stdout, info);
        pid = fork();
        if (pid > 0) {
            info->pids[i] = pid;
        } else if (pid == 0) {
            char path[30] = "./";
            strcat(path, info->sw_param[i].SwBlock);
            execl(path, info->sw_param[i].SwBlock,
                  info->sw_param[i].App_params[0],
                  info->sw_param[i].App_params[1],
                  info->sw_param[i].App_params[2], (char *) 0);
        }
    }
}

void restartProcess(swManager *info, int index) {
    pid_t pid;
    pid = fork();
    if (pid > 0) {
        info->pids[index] = pid;
        strcpy(info->sw_info[index].start_time, getTime());
    } else if (pid == 0) {
        char path[30] = "./";
        strcat(path, info->sw_param[index].SwBlock);
        execl(path, info->sw_param[index].SwBlock,
              info->sw_param[index].App_params[0],
              info->sw_param[index].App_params[1],
              info->sw_param[index].App_params[2], (char *) 0);
    }
}

int FindIndex(const swManager *info) {
    for (int i = 0; i < info->p_no; i++)
        if (info->dpid == info->pids[i])
            return i;
    return -1;
}

void LogWrite(FILE *log_file, const swInfo *list) {
    fprintf(log_file, "process name: %s\trestart count: %s\tstart time:%s\treason: %s\n",
            list->name, list->restart_count, list->start_time, list->reason);
}

void LogInterface(const swManager *info) {
    system("clear");
    printf("_____________________________________________________________________________________________\n");
    printf("| Process name | Restart count | Start time |Reason |\n");
    printf("|______________|_______________|_________________________|____________________________________ |\n");
    for (int i = 0; i < info->p_no; i++) {
        printf("| %12s |", info->sw_info[i].name);
        printf(" %13s |", info->sw_info[i].restart_count);
        printf(" %s|", info->sw_info[i].start_time);
        printf(" %34s |\n", info->sw_info[i].reason);
    }
    printf("|______________|_______________|_________________________|____________________________________ |\n");
}

char *rtrim(const char *s) {
    while (isspace(*s) || !isprint(*s)) ++s;
    return strdup(s);
}

char *ltrim(const char *s) {
    char *r = strdup(s);
    if (r != NULL) {
        char *fr = r + strlen(s) - 1;
        while ((isspace(*fr) || !isprint(*fr) || *fr == 0) && fr >= r) --fr;
        *++fr = 0;
    }
    return r;
}

char *trim(const char *s) {
    char *r = rtrim(s);
    char *f = rtrim(r);
    free(r);
    return f;
}

char *getTime(void) {
    struct timeval tv;
    gettimeofday(&tv, (char *) 0);
    time_t t = (time_t) tv.tv_sec;
    struct tm *ptm = localtime(&t);
    static char str[1024];
    sprintf(str, "%04d.%02d.%02d %02d:%02d:%02d.%03d ",
            ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,
            ptm->tm_hour, ptm->tm_min, ptm->tm_sec, (int) tv.tv_usec / 1000);
    return str;
}
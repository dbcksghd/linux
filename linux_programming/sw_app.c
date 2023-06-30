#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#define LOGDIR "./log"
#define LOGFILE "mylog"

char *gettime(void) {
    struct timeval tv;

    gettimeofday(&tv, NULL);

    time_t t = (time_t) tv.tv_sec;

    struct tm *ptm = localtime(&t);

    static char str[1024];

    sprintf(str, "%04d.%02d.%02d %02d:%02d:%02d.%03d ",

            ptm->tm_year + 1900, ptm->tm_mon + 1, ptm->tm_mday,

            ptm->tm_hour, ptm->tm_min, ptm->tm_sec, (int) tv.tv_usec / 1000);

    return str;
}

int main(int argc, char **argv) {

    struct timeval tv;

    gettimeofday(&tv, NULL);

    srand(tv.tv_usec);

    int ran = random();

    mkdir(LOGDIR, 0755);

    chdir(LOGDIR);

    FILE *fp;

    fp = fopen(LOGFILE, "a");

    fprintf(fp, "process name: %s\t", argv[0]);
    for (int k = 1; k < argc; k++)
        fprintf(fp, "%s ", argv[k]);

    fprintf(fp, "start time: %s\n", gettime());

    fclose(fp);

    sleep(ran % 20 + 1);

    if (ran % 2) {
        int signum = ((ran / 2) % 15 + 1);
        FILE *fp;
        fp = fopen(LOGFILE, "a");
        fprintf(fp, "process name: %s\t", argv[0]);
        for (int k = 1; k < argc; k++) {
            fprintf(fp, "%s ", argv[k]);
        }
        fprintf(fp, "crash time: %s\t", gettime());
        fprintf(fp, "SIGNAL(%d).%s\n", signum, strsignal(signum));
        fclose(fp);
        kill(getpid(), signum);
    } else {
        int exitval = (ran / 2) % 256;
        FILE *fp;
        fp = fopen(LOGFILE, "a");
        fprintf(fp, "process name: %s\t", argv[0]);
        for (int k = 1; k < argc; k++) {
            fprintf(fp, "%s ", argv[k]);
        }
        fprintf(fp, "crash time: %s\t", gettime());
        fprintf(fp, "EXIT(%d)\n", exitval);
        fclose(fp);
        exit(exitval);
    }
}
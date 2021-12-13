#include <stddef.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdint.h> 
#include <limits.h>

typedef uint64_t uint64;

static void s1_handler(int sig, siginfo_t *info, void *context) {
    char buff[128];
    snprintf(buff, 128, "%d", info->si_value.sival_int);
    if (sig == SIGTERM) {
        write(fileno(stderr), "Data: ", strlen("Data: "));
        write(fileno(stderr), buff, strlen(buff));
        write(fileno(stderr), "\n", 1);
        return;
    } 
}

int main() {
    pid_t pid = fork();
    char buff[256];
    int status;

    if (pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        struct sigaction action;
        sigemptyset(&action.sa_mask);
        action.sa_sigaction = &s1_handler;
        action.sa_flags = SA_RESTART | SA_SIGINFO;  // to get the value sent over sigqueue
        sigaction(SIGTERM, &action, NULL);
        for (; ;) sleep(10);
        exit(EXIT_SUCCESS);
    } else {
        pid = fork();
        //call child SR
        if (pid == 0) {
            snprintf(buff, sizeof(buff), "%d", getpid()-1);
            execl("./E1", "/.E1", buff, NULL);
            exit(EXIT_SUCCESS);
        } else {
            pid = fork();
            //call child ST
            if (pid == 0) {
                snprintf(buff, sizeof(buff), "%d", getpid()-2);
                execl("./E2", "/.E2", buff, NULL);
                exit(EXIT_SUCCESS);
            } else {
                sleep(3); 
                //parent default
                printf("Exiting from parent --> %d\n", getpid());
                wait(&status);
            }
        } 
    }
    return 0;
}
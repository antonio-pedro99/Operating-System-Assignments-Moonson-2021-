#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define PROG_1_FIFO_NAME "./FIFO_PROG_1"
#define PROG_2_FIFO_NAME "./FIFO_PROG_2"
#define STRING_SIZE 5

int flag = 0;

pid_t child_pid;

struct request {
    char *data[5];
};

struct response{
    /* data */
    int highest;
    int lowest;
    char *data[120];
};


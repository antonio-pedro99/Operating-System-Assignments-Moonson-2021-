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
int firstFivesSent = 0;

struct message {
    int id;
    char string[5];
};

struct response{
    int highest;
};


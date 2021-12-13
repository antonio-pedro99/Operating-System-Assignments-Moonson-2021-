#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#define MAX_MESSAGE_SIZE 128
#define PROG_1_SOCKET_NAME "./SOCKP1"
#define PROG_2_SOCKET_NAME "./SOCKP2"

#define STRING_SIZE 5
#define MAX_MSG_SIZE  256
#define MAX_MSG 50
#define BUFF_SIZE MAX_MSG_SIZE + 50

#define SIZE 52

int fd_s1;
int fd_s2;
int flag = 0;
int firstFivesSent = 0;

struct message {
    int id;
    char string[5];
};

struct response{
    int highest;
};


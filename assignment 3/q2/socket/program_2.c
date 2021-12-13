#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "constants.h"

int getHighest(int *array)
{
    int highest = array[0];

    for (int i = 0; i < 5; i++)
    {
        if (array[i] > highest)
        {
            highest = array[i];
        }
    }
    return highest;
}

int main(int argc, const char *argv[])
{
    struct message *msg;
    struct response res;
    int *tmp = (int *)calloc(5, sizeof(int)); // array of id of the strings

    char in[128];
    char out[128];

    struct sockaddr_un p2_addr;
    struct sockaddr_un p1_addr;

    size_t receive;
    size_t send;
    socklen_t len;

    p2_addr.sun_family = AF_UNIX;
    memcpy(p2_addr.sun_path, PROG_2_SOCKET_NAME, strlen(PROG_2_SOCKET_NAME) + 1);

    if ((fd_s2 = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1)
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    unlink(PROG_2_SOCKET_NAME);
    if (bind(fd_s2, (struct sockaddr *)&p2_addr, sizeof(p2_addr)) == -1)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    int i = 0;
    res.highest = 4;

    while (!flag)
    {

        printf("Received String in the range[%2d - %2d]\n", res.highest - 4, res.highest);
        for (int j = res.highest - 4; j <= res.highest; j++)
        {
            receive = recvfrom(fd_s2, in, 128, 0, (struct sockaddr *)&p1_addr, &len);
            if (receive == -1) {
                perror("receive");
                exit(EXIT_FAILURE);
            }

            msg = (struct message *)in;

            for (int i = 0; i < 5; i++) {
                tmp[i] = msg->id;
            }
            printf("String[%2d]: %s\n", msg->id, msg->string);
        }

        res.highest = getHighest(tmp);

        p1_addr.sun_family = AF_UNIX;
        memcpy(p1_addr.sun_path, PROG_1_SOCKET_NAME, strlen(PROG_1_SOCKET_NAME) + 1);

        send = sendto(fd_s2, (char *)&res, sizeof(struct message), 0, (struct sockaddr *)&p1_addr, sizeof(p1_addr));
        if (send == -1)
        {
            perror("send");
            continue;
        }
        printf("Sent Data Back %d\n", res.highest);
      
        if (res.highest == 49) {
            flag = 1;
        }
    }

    return 0;
}

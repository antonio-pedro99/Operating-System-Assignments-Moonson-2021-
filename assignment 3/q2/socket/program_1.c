#include <stdio.h>
#include <stdlib.h>
#include "constants.h"

int main(int argc, const char *argv[])
{

    char *strings = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char *arr[50] = {NULL}; // array of strings

    char out[128];
    char in[128];

    struct message msg;
    struct response *res;

    struct sockaddr_un p1_addr;
    struct sockaddr_un p2_addr;

    size_t send;
    size_t receive;
    socklen_t len;

    srand(time(NULL));
    for (int i = 0; i < 50; i++)
    {
        arr[i] = calloc(STRING_SIZE + 1, 1);
        for (int j = 0; j < STRING_SIZE; j++)
        {
            arr[i][j] = strings[rand() % SIZE];
        }
        arr[i][STRING_SIZE] = 0;
    }

    p1_addr.sun_family = AF_UNIX;
    memcpy(p1_addr.sun_path, PROG_1_SOCKET_NAME, strlen(PROG_1_SOCKET_NAME) + 1);

    p2_addr.sun_family = AF_UNIX;
    memcpy(p2_addr.sun_path, PROG_2_SOCKET_NAME, strlen(PROG_2_SOCKET_NAME) + 1);

    if ((fd_s1 = socket(AF_UNIX, SOCK_DGRAM, 0)) == -1)
    {
        perror("Socket cannot be instantiated");
        exit(EXIT_FAILURE);
    }

    unlink(PROG_1_SOCKET_NAME);
    if (bind(fd_s1, (struct sockaddr *)&p1_addr, sizeof(p1_addr)) == -1)
    {
        perror("Cannot bind socket");
        exit(EXIT_FAILURE);
    }

    int highest = 0; 

    while (!flag)
    {
          int from = (!firstFivesSent) ? 0 : highest + 1;
          int to = (!firstFivesSent) ? 4 : highest + 5;

          printf("Sending from %d to %d\n", from, to); 

       for (int i = from; i <= to; i++)
        {
            sprintf(out, "%s", arr[i]);
            strcpy(msg.string, out);
            msg.id = i;
            send = sendto(fd_s1, (char *)&msg, sizeof(struct message), 0, (struct sockaddr *)&p2_addr, sizeof(p2_addr));
            if (send == -1)
            {
                perror("send");
                continue;
            }
        } 
        firstFivesSent = 1;
        printf("Data sent\n");
        receive = recvfrom(fd_s1, in, 128, 0, (struct sockaddr *)&p2_addr, &len);
        if (receive == -1)
        {
            perror("receive");
            continue;
        }

        res = (struct response *) in;
        highest = res->highest;

        if (res->highest != 49)
        {
            printf("Response got\n");
            printf("Highest ID: %d\n", highest);
        }
        else
        {
            printf("No Data to be sent\n");
            flag = 1;
        }
        sleep(1);
    }

    return 0;
}
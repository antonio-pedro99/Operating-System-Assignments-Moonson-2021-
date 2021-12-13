#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"
#define SIZE 52
int main(int argc, char *argv[])
{

    char *strings = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char *arr[50] = {NULL}; // array of strings

    mqd_t mqd_server, mq_client;

    struct mq_attr attr;
    char input_buff[266];
    char output_buff[266];
    struct message msg;
    struct response *res;
    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;
    attr.mq_curmsgs = 0;

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

    if ((mqd_server = mq_open(PROG_1_QUEUE_NAME, O_RDONLY | O_CREAT, 0660, &attr)) == -1)
    {
        perror("open queue");
        exit(EXIT_FAILURE);
    }

    res->highest = 4;
    res->lowest = 0;

    int highest = 0;
    printf("Executing P1\n");
    while (!flag)
    {

        if ((mq_client = mq_open(PROG_2_QUEUE_NAME, O_WRONLY)) == 1)
        {
            perror("open client");
            continue;
        }

        int from = (!firstFivesSent) ? 0 : highest + 1;
        int to = (!firstFivesSent) ? 4 : highest + 5;

        printf("from %d to %d\n", from, to);

        for (int i = from; i <= to; i++)
        {
            sprintf(output_buff, "%s", arr[i]);
            strcpy(msg.string, output_buff);
            msg.id = i;
            if (mq_send(mq_client, (char *)&msg, attr.mq_msgsize, 0) == -1)
            {
                if (errno == EBADF)
                {
                    continue;
                }
                else
                {
                    perror("server failure");
                }
                continue;
            }
        }
        
        firstFivesSent = 1;
        if (mq_receive(mqd_server, input_buff, attr.mq_msgsize, NULL) == -1)
        {
            perror("receive");
        }
        res = (struct response *)input_buff;
        int tmp = res->highest;
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
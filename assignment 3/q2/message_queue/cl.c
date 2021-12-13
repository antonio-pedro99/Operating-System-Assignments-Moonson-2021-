#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"

int getHighest(int *array) {
    int highest = array[0];

    for (int i = 0 ; i < 5; i++) {
        if (array[i] > highest) {
            highest = array[i];
        }
    }

    return highest;
}

int main(int argc, char *argv[])
{

    mqd_t mqd_server, mq_client;
    int *tmp = (int*) calloc(5, sizeof(int));//array of id of the strings

    struct mq_attr attr;
    char input_buff[266];
    char output_buff[266];

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 256;
    attr.mq_curmsgs = 0;

    struct message *msg;
    struct response res;

    char buff[266];

    if ((mq_client = mq_open(PROG_2_QUEUE_NAME, O_RDONLY | O_CREAT, 0660, &attr)) == -1)
    {
        perror("open queue client");
        exit(EXIT_FAILURE);
    }

    if ((mqd_server = mq_open(PROG_1_QUEUE_NAME, O_WRONLY)) == -1)
    {
        perror("open queue server");
        exit(EXIT_FAILURE);
    }

    printf("Executing P2\n");
    res.highest = 4;
    res.lowest = 0;

    while (!flag)
    {
        /* code */
        printf("Received String in the range[%2d - %2d]\n", res.highest-4, res.highest);
        for (int j = res.highest-4; j <= res.highest; j++)
        {
            if (mq_receive(mq_client, buff, attr.mq_msgsize, NULL) == -1)
            {
                perror("receive");
                exit(EXIT_FAILURE);
            }
            msg = (struct message *)buff;
            for (int i = 0; i < 5; i++) {
                tmp[i] = msg->id;
            }
            printf("String[%2d]: %s\n", msg->id, msg->string);
        }

        res.highest = getHighest(tmp); 
        printf("Trying to send aknowledge...\n");
        if (mq_send(mqd_server, (char *)&res, attr.mq_msgsize, 0) == -1)
        {
            perror("failed to send to Server");
            continue;
        }
        printf("Sent back: %d\n", res.highest);
        sleep(1);

        if (res.highest == 49) {
            flag = 1;
        }
    }

    if (mq_close(mq_client) == -1)
    {
        perror("close");
        exit(EXIT_FAILURE);
    }
    if (mq_unlink(PROG_2_QUEUE_NAME) == -1)
    {
        perror("unlike");
        exit(EXIT_FAILURE);
    }

    return 0;
}
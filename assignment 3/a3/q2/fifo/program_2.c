#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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

int main(int argc, char *argv[])
{
    int fd;
    struct message msg;
    struct response res;
    int *tmp = (int *)calloc(5, sizeof(int));

    res.highest = 4;

    umask(0);
    if (mkfifo(PROG_2_FIFO_NAME, S_IFIFO | S_IRUSR | S_IWUSR | S_IWGRP | 0660) == -1)
    {
        if (errno == EEXIST)
        {
            printf("Using the existing...\n");
        }
        else
        {
            perror("fifo permission");
            exit(EXIT_FAILURE);
        }
    }

    while (!flag)
    {
        printf("P2 is being executed\n");
        if ((fd = open(PROG_1_FIFO_NAME, O_RDONLY)) == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        printf("Received String in the range[%2d - %2d]\n", res.highest - 4, res.highest);

        for (int i = res.highest - 4; i <= res.highest; i++)
        {
            if (read(fd, &msg, sizeof(struct message)) == -1)
            {
                perror("read");
                exit(EXIT_FAILURE);
            }

            for (int j = 0; j < 5; j++)
            {
                tmp[j] = msg.id;
            }
            printf("String[%2d]: %s\n", i, msg.string);
        }

        // finally close
        close(fd);
        // writing response to P1 FIFO
        int response_fd = open(PROG_2_FIFO_NAME, O_WRONLY);

        if (response_fd == -1)
        {
            perror("open");
        }

        res.highest = getHighest(tmp);

        if (res.highest == 49)
        {
            flag = 1;
        }
        write(response_fd, &res, sizeof(struct response));
        sleep(1);
        close(response_fd);
    }

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "constants.h"

#define SIZE 52

int main(int argc, char *argsv[])
{
    char *strings = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char *arr[50] = {NULL}; // array of strings
    int fd_request, fd_response;

    struct message msg;
    struct response res;

    srand(time(NULL));
    for (int i = 0; i < 50; i++)
    {
        arr[i] = calloc(STRING_SIZE + 1, 1);
        for (int j = 0; j < STRING_SIZE; j++)
        {
            arr[i][j] = strings[rand() % SIZE];
        }
        arr[i][STRING_SIZE] = 0;
        // printf("[%2d]: %s\n", i, arr[i]);
    }

    // first 5 strings
    res.highest = 4;

    int highest = 0;
    // creating the fifo, if it already exists, use the existing one.
    umask(0);
    if (mkfifo(PROG_1_FIFO_NAME, S_IFIFO | S_IRUSR | S_IWUSR | S_IWGRP | 0660) == -1)
    {
        if (errno == EEXIST)
        {
            printf("Using the existing...\n");
        }
        else
        {
            perror("fifo");
            exit(EXIT_FAILURE);
        }
    }

    // writing
    // preparing the data
    while (!flag)
    {
        /* Open the P1 FIFO
         * And Write the request to P1 FIFO
         */

        if ((fd_request = open(PROG_1_FIFO_NAME, O_WRONLY)) == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        int from = (!firstFivesSent) ? 0 : highest + 1;
        int to = (!firstFivesSent) ? 4 : highest + 5;

        for (int i = from; i <= to; i++)
        {
            strcpy(msg.string, arr[i]);
            msg.id = i;

            if (write(fd_request, &msg, sizeof(struct message)) == -1)
            {
                perror("write");
                exit(EXIT_FAILURE);
            }
            free(arr[i]);
        }

        firstFivesSent = 1;
        // finally close
        close(fd_request);

        if ((fd_response = open(PROG_2_FIFO_NAME, O_RDONLY)) == -1)
        {
            perror("open");
            exit(EXIT_FAILURE);
        }

        if (read(fd_response, &res, sizeof(struct response)) != sizeof(struct response))
        {
            perror("response");
        }
        highest = res.highest;
        close(fd_response);
        if (res.highest != 49)
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
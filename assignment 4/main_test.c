#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <errno.h>
#include <linux/random.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>

void consumer();
void producer();


pthread_mutex_t mutex;

int main(){
    pthread_t prod, cons;

    pthread_mutex_init(&mutex, NULL);
  

    if (pthread_create(&prod, NULL, (void *)producer, 0) == -1) {
        perror("create producer");
    }

    if (pthread_create(&cons, NULL, (void *)consumer, 0) == -1) {
        perror("create consumer");
    }

    if (pthread_join(prod, NULL) == -1) {
        perror("join producer");
    }

    if (pthread_join(cons, NULL) == -1) {
        perror("join consumer");
    }

    pthread_mutex_destroy(&mutex);
    return 0;
}

void producer(){

    int fd_urandom = open("/dev/urandom", O_RDONLY);
    char buff[255];

    if (fd_urandom == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    printf("Consumer Process\n");
    for (;;) {
        if (read(fd_urandom, buff, 255) == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }
        syscall(549, buff, strlen(buff), mutex);
        printf("Read successfully\n");
    }
    exit(EXIT_SUCCESS);
}

void consumer() {
    printf("Consumer Process\n");
    char *buff;
    for (;;) {
        syscall(550, buff, strlen(buff), mutex);
    }
    exit(EXIT_SUCCESS);
}
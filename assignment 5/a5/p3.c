#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <sys/un.h>

#define N 5
#define IS_THNKING 0
#define IS_HUNGRY 1
#define IS_EATING 2
#define LEFT (p + 4) % N
#define RIGHT (p + 1) % N

sem_t _fork;
sem_t _bowls;

sem_t semaphores[N];

void *philosopher_try_eat(void *total);
void take_the_fork(int);
void put_the_fork(int);
void take_the_bowl(int);
void put_the_bowl(int);
void think(int n, pthread_t *id);
void startEating(int);
int state[N];
int n[N] = {0, 1, 2, 3, 4};

int main()
{
    pthread_t _id_thread[5];
    int k = 0;

    sem_init(&_fork, 0, 1);
    sem_init(&_bowls, 0, 4);
    // start the philos
    while (k < 5)
    {
        sem_init(&semaphores[k], 0, 0);
        k++;
    }

    think(k, _id_thread);

    for (k = 0; k < 5; k++)
    {
        pthread_join(_id_thread[k], NULL);
    }
}

void think(int p, pthread_t *id)
{
    p = 0;
    while (p < 5)
    {
        pthread_create(&id[p], NULL, philosopher_try_eat, &n[p]);
        printf("philosopher [%d] is thinking\n", p + 1);
        p++;
    }
}

void *philosopher_try_eat(void *total)
{
    while (1)
    {
        int *i = total;
        sleep(1);
        take_the_fork(*i);
        sleep(0);
        put_the_fork(*i);
    }
}

void take_the_fork(int p) {
    sem_wait(&_fork);
    sem_wait(&_bowls);

    state[p] = IS_HUNGRY;
    printf("the philosopher [%d] is hungry!\n", p + 1);
    startEating(p);
    sem_post(&_fork);
    sem_post(&_bowls);
    sem_wait(&semaphores[p]);
    sleep(1);
}

int isEating(int p)
{
    return (state[p] == IS_EATING) ? 1 : 0;
}

int isHungry(int p)
{
    return (state[p] == IS_HUNGRY) ? 1 : 0;
}

int isThinking(int p)
{
    return (state[p] == IS_THNKING) ? 1 : 0;
}

int forkAvailable(int f)
{
    return (state[f] != IS_EATING) ? 1 : 0;
}

void startEating(int p)
{
    if (isHungry(p) && forkAvailable(LEFT) && forkAvailable(RIGHT))
    {
        state[p] = IS_EATING;
        sleep(2);
        printf("philosopher %d took fork %d\n", p+1, LEFT);
        printf("philosopher %d is eating\n", p+1);
        sem_post(&semaphores[p]);
    }
}


void put_the_fork(int p)
{
    sem_wait(&_fork);
    sem_wait(&_bowls);
    state[p] = IS_THNKING;
    printf("the philosopher [%d] is putting the fork %d\n", p + 1, LEFT);
    printf("the philosopher [%d] is thinking! \n", p + 1);
    startEating(LEFT);
    startEating(RIGHT);
    sem_post(&_fork);
    sem_post(&_bowls);
}
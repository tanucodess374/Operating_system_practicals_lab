#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define N 5

sem_t chopsticks[N];
sem_t room;

void *philosopher(void *arg) {
    int id = *(int *)arg;

    printf("Philosopher %d is thinking.\n", id);

    sleep(1);

    sem_wait(&room);

    sem_wait(&chopsticks[id]);
    sem_wait(&chopsticks[(id + 1) % N]);

    printf("Philosopher %d is eating.\n", id);

    sleep(2);

    printf("Philosopher %d has finished eating.\n", id);

    sem_post(&chopsticks[(id + 1) % N]);
    sem_post(&chopsticks[id]);

    sem_post(&room);

    printf("Philosopher %d is thinking again.\n", id);

    return NULL;
}

int main() {
    pthread_t philosophers[N];
    int ids[N];

    sem_init(&room, 0, N - 1);

    for (int i = 0; i < N; i++) {
        sem_init(&chopsticks[i], 0, 1);
    }

    for (int i = 0; i < N; i++) {
        ids[i] = i;
        pthread_create(&philosophers[i], NULL,
                       philosopher, &ids[i]);
    }

    for (int i = 0; i < N; i++) {
        pthread_join(philosophers[i], NULL);
    }

    for (int i = 0; i < N; i++) {
        sem_destroy(&chopsticks[i]);
    }

    sem_destroy(&room);

    printf("\nAll philosophers have finished.\n");

    return 0;
}
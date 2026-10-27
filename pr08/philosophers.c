#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#define NUM_PHILOSOPHERS 5

pthread_mutex_t forks[NUM_PHILOSOPHERS];

void* philosopher(void *num) {
    int id = *(int*)num;
    int left_fork = id;
    int right_fork = (id + 1) % NUM_PHILOSOPHERS;

    // Устранение дедлока: упорядоченный захват вилок для философа с наибольшим ID
    if (id == NUM_PHILOSOPHERS - 1) {
        pthread_mutex_lock(&forks[right_fork]);
        pthread_mutex_lock(&forks[left_fork]);
    } else {
        pthread_mutex_lock(&forks[left_fork]);
        pthread_mutex_lock(&forks[right_fork]);
    }

    printf('Philosopher %d is eating.\n', id);
    sleep(1);

    pthread_mutex_unlock(&forks[left_fork]);
    pthread_mutex_unlock(&forks[right_fork]);
    return NULL;
}

int main() {
    printf('=== PR-8: Dining Philosophers (Deadlock-free Implementation) ===\n');
    pthread_t phils[NUM_PHILOSOPHERS];
    int ids[NUM_PHILOSOPHERS];

    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_mutex_init(&forks[i], NULL);
        ids[i] = i;
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_create(&phils[i], NULL, philosopher, &ids[i]);
    }
    for (int i = 0; i < NUM_PHILOSOPHERS; i++) {
        pthread_join(phils[i], NULL);
    }
    return 0;
}
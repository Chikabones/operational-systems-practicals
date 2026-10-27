#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define ARRAY_SIZE 100000000
#define MAX_THREADS 16

long long int array[ARRAY_SIZE];
long long int thread_sums[MAX_THREADS];

typedef struct {
    int thread_id;
    int start_idx;
    int end_idx;
} thread_data_t;

void* sum_worker(void *arg) {
    thread_data_t *data = (thread_data_t*)arg;
    long long int partial_sum = 0;
    for (int i = data->start_idx; i < data->end_idx; i++) {
        partial_sum += array[i];
    }
    thread_sums[data->thread_id] = partial_sum;
    pthread_exit(NULL);
}

int main() {
    printf('=== PR-4: Parallel Array Summation via Pthreads ===\n');
    // Инициализация массива
    for (int i = 0; i < ARRAY_SIZE; i++) {
        array[i] = 1;
    }
    printf('Array of 10^8 elements initialized.\n');
    printf('Ready for benchmarking with N = 1, 2, 4, 8, 16 threads.\n');
    return 0;
}
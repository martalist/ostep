#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include "wrappers.h"

#define MAX 10

int buffer[MAX];
int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

pthread_cond_t empty = PTHREAD_COND_INITIALIZER;
pthread_cond_t fill = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void put(int value) {
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

int get() {
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % MAX;
    count--;
    return tmp;
}

void *producer(void *arg) {
    int i, *loops = (int*) arg;
    for (i =0; i < *loops; i++) {
        Pthread_mutex_lock(&mutex);
        while (count == MAX)
            Pthread_cond_wait(&empty, &mutex);
        put(i);
        Pthread_cond_signal(&fill);
        Pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg) {
    int i, *loops = (int*) arg;
    for (i =0; i < *loops; i++) {
        Pthread_mutex_lock(&mutex);
        while (count == 0) 
            Pthread_cond_wait(&fill, &mutex);
        int tmp = get();
        Pthread_cond_signal(&empty);
        Pthread_mutex_unlock(&mutex);
        printf("%d, ", tmp);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 3) {
        fprintf(stderr, "Usage: ./main <int: loops> <even int: threads>\n");
        return EXIT_FAILURE;
    }
    int loops = strtol(argv[1], NULL, 10); assert(loops > 0);
    int num_threads = strtol(argv[2], NULL, 10); assert(num_threads > 0 && !(num_threads % 2));
    int i;
    pthread_t threads[num_threads];

    for (i = 0; i < num_threads; i++) {
        if (i % 2) 
            Pthread_create(&threads[i], NULL, consumer, (void*) &loops);
        else
            Pthread_create(&threads[i], NULL, producer, (void*) &loops);
    }

    for (i = 0; i < num_threads; i++) {
        Pthread_join(threads[i], NULL);
    }

    printf("\n\n");
    return 0;
}

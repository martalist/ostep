#include <assert.h>
#include <pthread.h>
#include <stdio.h>
#include "wrappers.h"

int buffer;
int count = 0;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

void put(int value) {
    assert(count == 0);
    count = 1;
    buffer = value;
}

int get() {
    assert(count ==1);
    count = 0;
    return buffer;
}

void *producer(void *arg) {
    int i, *loops = (int*) arg;
    for (i =0; i < *loops; i++) {
        Pthread_mutex_lock(&mutex);
        while (count == 1)
            Pthread_cond_wait(&cond, &mutex);
        put(i);
        Pthread_cond_signal(&cond);
        Pthread_mutex_unlock(&mutex);
    }
    return NULL;
}

void *consumer(void *arg) {
    int i, *loops = (int*) arg;
    for (i =0; i < *loops; i++) {
        Pthread_mutex_lock(&mutex);
        while (count == 0) 
            Pthread_cond_wait(&cond, &mutex);
        int tmp = get();
        Pthread_cond_signal(&cond);
        Pthread_mutex_unlock(&mutex);
        printf("%d\n", tmp);
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: ./main <int: loops>\n");
        return EXIT_FAILURE;
    }
    int loops = strtol(argv[1], NULL, 10); assert(loops > 0);
    pthread_t t1, t2;

    Pthread_create(&t1, NULL, producer, (void*) &loops);
    Pthread_create(&t2, NULL, consumer, (void*) &loops);

    Pthread_join(t1, NULL);
    Pthread_join(t2, NULL);
    return 0;
}

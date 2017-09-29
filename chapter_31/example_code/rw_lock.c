#include <assert.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include "../../chapter_29/counter.h"

typedef struct _rwlock_t {
    sem_t lock;         // binary semaphore (basic lock)
    sem_t writelock;    // used to allow ONE writer or MANY readers
    int readers;        // count of readers reading in critical section
} rwlock_t;

rwlock_t rw;
int shared, loops;
counter_t counter, total;

void rwlock_init(rwlock_t *rw) {
    rw->readers = 0;
    sem_init(&rw->lock, 0, 1);
    sem_init(&rw->writelock, 0, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw) {
    sem_wait(&rw->lock);
    rw->readers++;
    if (rw->readers == 1)
    sem_wait(&rw->writelock); // first reader acquires writelock
    sem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw) {
    sem_wait(&rw->lock);
    rw->readers--;
    if (rw->readers == 0)
    sem_post(&rw->writelock); // last reader releases writelock
    sem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
    sem_wait(&rw->writelock);
}

void rwlock_release_writelock(rwlock_t *rw) {
    sem_post(&rw->writelock);
}

void *reader(void *arg) {
    // do something
    int i;
    for (i = 0; i < loops; i++) {
        rwlock_acquire_readlock(&rw);
        if (shared >= 0) 
            counter_inc(&counter);
        counter_inc(&total);
        rwlock_release_readlock(&rw);
    }
    return NULL;
}

void *writer(void *arg) {
    // do something
    int i, c;
    for (i = 0; i < loops; i++) {
        rwlock_acquire_writelock(&rw);
        shared++;
        rwlock_release_writelock(&rw);
        c = counter_get(&counter); 
        if (c > 0) {
            counter_reset(&counter);
            printf("The number of reads before writer could execute was %d\n",
                    c);
        }
    }
    return NULL;
}

int main(int argc, char *argv[]) {
    int opt, i, rc;
    int nthreads = 2;
    int writers = 1;
    loops = 10;

    while ((opt = getopt(argc, argv, "w:l:t:")) != -1) {
        switch (opt) {
        case 't':
            nthreads = atoi(optarg);
            break;
        case 'l':
            loops = atoi(optarg);
            break;
        case 'w':
            writers = atoi(optarg);
            break;
        default: /* '?' */
            fprintf(stderr, "Usage: %s [-t] nthreads [-l] loops [-r] ratio-of-writers\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    assert(writers <= nthreads);
    shared = 0;
    rwlock_init(&rw);
    counter_init(&counter);
    counter_init(&total);
    pthread_t threads[nthreads];
    printf("loops: %d\n", loops);
    printf("threads: %d\n", nthreads);

    for (i = 0; i < nthreads; i++) {
        if (writers-- > 0)
            rc = pthread_create(&threads[i], NULL, writer, NULL);
        else
            rc = pthread_create(&threads[i], NULL, reader, NULL);
        if (rc != 0) {
            fprintf(stderr, "thread could not be created\n");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < nthreads; i++) {
        rc = pthread_join(threads[i], NULL);
        if (rc != 0) {
            fprintf(stderr, "thread failed to join\n");
            exit(EXIT_FAILURE);
        }
    }
    printf("total number of reads: %d\n", counter_get(&total));
    return 0;
}

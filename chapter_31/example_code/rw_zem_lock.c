/*
 * Same as rw_lock, however using our own semaphore, Zem_t,
 * as a proof of concept.
 */

#include <assert.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../chapter_29/counter.h"
#include "Zemaphores.c"

typedef struct _rwlock_t {
    Zem_t lock;         // binary semaphore (basic lock)
    Zem_t writelock;    // used to allow ONE writer or MANY readers
    int readers;        // count of readers reading in critical section
} rwlock_t;

rwlock_t rw;
int shared, loops;
counter_t counter, total;

void rwlock_init(rwlock_t *rw) {
    rw->readers = 0;
    Zem_init(&rw->lock, 1);
    Zem_init(&rw->writelock, 1);
}

void rwlock_acquire_readlock(rwlock_t *rw) {
    Zem_wait(&rw->lock);
    rw->readers++;
    if (rw->readers == 1)
        Zem_wait(&rw->writelock); // first reader acquires writelock
    Zem_post(&rw->lock);
}

void rwlock_release_readlock(rwlock_t *rw) {
    Zem_wait(&rw->lock);
    rw->readers--;
    if (rw->readers == 0)
        Zem_post(&rw->writelock); // last reader releases writelock
    Zem_post(&rw->lock);
}

void rwlock_acquire_writelock(rwlock_t *rw) {
    Zem_wait(&rw->writelock);
}

void rwlock_release_writelock(rwlock_t *rw) {
    Zem_post(&rw->writelock);
}

// common main to measure the results of the reader writer lock defined above
#include "main-common.c"

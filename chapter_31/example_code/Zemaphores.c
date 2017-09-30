/*
 * Implementing our own semaphore.
 * One subtle difference between our Zemaphore and pure semaphores 
 * as defined by Dijkstra is that we don’t maintain the invariant 
 * that the value of the semaphore, when negative, reflects the 
 * number of waiting threads
 */

#ifndef __ZEMAPHORE
#define __ZEMAPHORE

#include "../../chapter_29/wrappers.h"

typedef struct __Zem_t {
    int value;
    pthread_cond_t cond;
    pthread_mutex_t lock;
} Zem_t;

void Zem_init(Zem_t *z, int value) {
    z->value = value;
    Pthread_mutex_init(&z->lock, NULL);
    Cond_init(&z->cond, NULL);
}

void Zem_wait(Zem_t *z) {
    Pthread_mutex_lock(&z->lock);
    while (z->value <= 0)
        Cond_wait(&z->cond, &z->lock);
    z->value--;
    Pthread_mutex_unlock(&z->lock);
}

void Zem_post(Zem_t *z) {
    Pthread_mutex_lock(&z->lock);
    z->value++;
    Cond_signal(&z->cond);
    Pthread_mutex_unlock(&z->lock);
}

#endif

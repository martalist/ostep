#include <stdio.h>
#include <stdlib.h>

#include "mythreads.h"

int balance = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void* worker(void* arg) {
    Pthread_mutex_lock(&lock);
    balance++; // unprotected access
    Pthread_mutex_unlock(&lock);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);

    Pthread_mutex_lock(&lock);
    balance++; // unprotected access
    Pthread_mutex_unlock(&lock);

    Pthread_join(p, NULL);
    return 0;
}

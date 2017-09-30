#include "../../chapter_29/wrappers.h"
#ifndef __MAIN_COMM
#define __MAIN_COMM

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
    int opt, i;
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

    // make sure the user input is legal
    assert(nthreads > 0);
    assert(writers <= nthreads && writers >= 0);

    // Prepare to spin up reader/writer threads
    shared = 0;
    rwlock_init(&rw);
    counter_init(&counter);
    counter_init(&total);
    pthread_t threads[nthreads];
    printf("loops: %d\n", loops);
    printf("threads: %d\n", nthreads);

    for (i = 0; i < nthreads; i++) {
        // interleave reader/writer creation, rather than all one type before the other
        if (writers == nthreads || (i % 2 && writers-- > 0)) 
            Pthread_create(&threads[i], NULL, writer, NULL);
        else
            Pthread_create(&threads[i], NULL, reader, NULL);
    }

    for (i = 0; i < nthreads; i++) {
        Pthread_join(threads[i], NULL);
    }
    printf("total number of reads: %d\n", counter_get(&total));
    return 0;
}

#endif

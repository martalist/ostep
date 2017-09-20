#include <stdio.h>
#include "counter.h"
#include "defaults.h"
#include "llist.h"

typedef struct __myargs_t {
    int loops;
    counter_t *counter;
    int mytid;
    llist_t *list;
    int key;
} myargs_t;

void *build_list(void *arg) {
    myargs_t *a = (myargs_t *) arg;
    // do some work
    int i, key;
    for (i = 0; i < a->loops; i++) {
        key = counter_inc_and_get(a->counter);
        ll_insert(a->list, key);
    }
    return NULL;
}

void *search_list(void *arg) {
    myargs_t *a = (myargs_t *) arg;
    int rc;
    double total;
    struct timeval start, end;

    rc = gettimeofday(&start, NULL);         // set timer
    if (rc != 0) {
        fprintf(stderr, "gettimeofday error\n");
        return (void *) EXIT_FAILURE;
    }
    int index = ll_indexof(a->list, a->key); // find the key
    rc = gettimeofday(&end, NULL);           // end timer
    if (rc != 0) {
        fprintf(stderr, "gettimeofday error\n");
        return (void *) EXIT_FAILURE;
    }
    total = (end.tv_sec - start.tv_sec) * MILLION + (end.tv_usec - start.tv_usec);

    printf("%d was found at index %d by thread #%d in %f seconds\n", 
            a->key, index, a->mytid, total / MILLION);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc <= 2) {
        fprintf(stderr, "Usage: ./main <int: loops> <int: threads>\n");
        return 1;
    }
    
    int loops, num_threads;
    loops = strtol(argv[1], NULL, BASE_10);
    num_threads = strtol(argv[2], NULL, BASE_10);
    if (!loops || !num_threads) {
        fprintf(stderr, "Usage: ./main <int: loops> <int: threads>\n");
        return 1;
    }
    if (num_threads > MAX_THREADS) {
        fprintf(stderr, "Let's not go crazy. Choose %d or less threads.\n", MAX_THREADS);
        return 1;
    }

    pthread_t threads[num_threads];
    int i;
    counter_t counter;
    counter_init(&counter);
    llist_t list;
    ll_init(&list);
    myargs_t args[num_threads];

    // build the list
    for (i = 0; i < num_threads; i++) {
        args[i].mytid = i;      // thread ID
        args[i].loops = loops;
        args[i].counter = &counter;
        args[i].list = &list;
        Pthread_create(&threads[i], NULL, build_list, &args[i]);
    }
    for (i = 0; i < num_threads; i++) {
        Pthread_join(threads[i], NULL);
    }

    // Send the threads to find keys in the list
    for (i = 0; i < num_threads; i++) {
        args[i].key = (num_threads * loops) / (num_threads - i);
        Pthread_create(&threads[i], NULL, search_list, &args[i]);
    }
    for (--i; i >= 0; i--) {
        Pthread_join(threads[i], NULL);
    }

    /* printf("Summary\n\tExpected nodes:\t%d\n\tActual nodes:\t%d\n\n", */
            /* num_threads * loops, ll_length(&list)); */
    printf("\nThe counter got to %d (expected %d)\n\n", 
            counter_get(&counter), num_threads * loops);

    return 0;
}

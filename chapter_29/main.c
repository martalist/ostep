#include <stdio.h>
#include <sys/time.h>
#include "wrappers.h"
#include "counter.c"

#define BASE_10 10
#define MILLION 0xf4240
#define MAX_THREADS 20

typedef struct __myargs_t {
    int loops;
    counter_t counter;
} myargs_t;

void *worker(void *arg) {
    myargs_t *a = (myargs_t *) arg;
    struct timeval *start = Malloc(sizeof(struct timeval));
    struct timeval *end = Malloc(sizeof(struct timeval));
    int rc, i;

    rc = gettimeofday(start, NULL);
    if (rc != 0) {
        fprintf(stderr, "gettimeofday error\n");
        return (void *) -1;
    }

    long time;
    for (i = 0; i < a->loops; i++) {
        counter_inc(&a->counter);
    }

    rc = gettimeofday(end, NULL);
    if (rc != 0) {
        fprintf(stderr, "gettimeofday error\n");
        return (void *) -1;
    }

    time = (end->tv_sec - start->tv_sec) * MILLION +
        (end->tv_usec - start->tv_usec);
    return (void *) time;
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

    if (num_threads > MAX_THREADS) {
        fprintf(stderr, "Let's not go crazy. Choose %d or less threads.\n", MAX_THREADS);
        return 1;
    }

    pthread_t threads[num_threads];
    long time[num_threads];
    double total = 0;
    int i;
    counter_t counter;
    counter_init(&counter);
    myargs_t args;
    args.loops = loops;
    args.counter = counter;

    for (i = 0; i < num_threads; i++) {
        Pthread_create(&threads[i], NULL, worker, &args);
    }

    for (i = 0; i < num_threads; i++) {
        Pthread_join(threads[i], (void **) &time[i]);
    }

    for (i = 0; i < num_threads; i++) {
        total += (double) time[i];  // microseconds
    }
    
    printf("%d threads incrementing a locked (monitor) counter %d times each took %f seconds.\n\n",
            num_threads, loops, total / MILLION);

    return 0;
}

#include <stdio.h>
#include <sys/time.h>
#include "wrappers.h"
#include "counter.c"

#define BASE_10 10
#define MILLION 0xf4240

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
    if (argc <= 1) {
        fprintf(stderr, "Usage: ./main <int: loops>\n");
        return 1;
    }
    
    pthread_t t1, t2;
    long time1, time2;
    counter_t counter;
    counter_init(&counter);
    int loops = strtol(argv[1], NULL, BASE_10);
    myargs_t args;
    args.loops = loops;
    args.counter = counter;

    Pthread_create(&t1, NULL, worker, &args);
    Pthread_create(&t2, NULL, worker, &args);

    Pthread_join(t1, (void **) &time1);
    Pthread_join(t2, (void **) &time2);

    printf("Two threads incrementing a locked (monitor) counter %d times each\n", loops);
    printf("took %f seconds.\n\n", ((double) (time1 + time2)) / MILLION);

    return 0;
}

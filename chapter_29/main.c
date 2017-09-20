#include <stdio.h>
#include <sys/time.h>
#include "wrappers.h"
#include "counter.c"
#include "defaults.h"

typedef struct __myargs_t {
    int loops;
    counter_t *counter;
} myargs_t;

void *worker(void *arg) {
    myargs_t *a = (myargs_t *) arg;
    int i;
    for (i = 0; i < a->loops; i++) {
        counter_inc(a->counter);
    }
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

    if (num_threads > MAX_THREADS) {
        fprintf(stderr, "Let's not go crazy. Choose %d or less threads.\n", MAX_THREADS);
        return 1;
    }

    pthread_t threads[num_threads];
    long time[num_threads];
    double total;
    int i, rc;
    counter_t counter;
    counter_init(&counter);
    myargs_t args;
    args.loops = loops;
    args.counter = &counter;
    struct timeval start, end;

    rc = gettimeofday(&start, NULL);
    if (rc != 0) {
        fprintf(stderr, "gettimeofday error\n");
        return 1;
    }

    for (i = 0; i < num_threads; i++) {
        Pthread_create(&threads[i], NULL, worker, &args);
    }

    for (i = 0; i < num_threads; i++) {
        Pthread_join(threads[i], (void **) &time[i]);
    }

    rc = gettimeofday(&end, NULL);
    if (rc != 0) {
        fprintf(stderr, "gettimeofday error\n");
        return 1;
    }

    total = (end.tv_sec - start.tv_sec) * MILLION + (end.tv_usec - start.tv_usec);
    
    printf("%d threads incrementing a locked (monitor) counter %d times each took %f seconds.\n\n",
            num_threads, loops, total / MILLION);
    printf("Counter:\n\tExpected:\t%d\n\tActual: \t%d\n\n", 
            loops * num_threads, counter_get(&counter));

    return 0;
}

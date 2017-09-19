#include <stdio.h>
#include "defaults.h"
#include "sloppy_counter.h"

typedef struct __myargs_t {
    int loops;
    scounter_t counter;
} myargs_t;

void *worker(void *arg) {
    myargs_t *a = (myargs_t *) arg;
    pthread_t tid = pthread_self();
    int i;
    for (i = 0; i < a->loops; i++) {
        update(&a->counter, tid, 1);
    }
    return NULL;
}


int main(int argc, char *argv[])
{
    if (argc <= 3) {
        fprintf(stderr, "Usage: ./main <int: loops> <int: threads> <int: threshold>\n");
        return 1;
    }
    
    int loops, num_threads, threshold;
    loops = strtol(argv[1], NULL, BASE_10);
    num_threads = strtol(argv[2], NULL, BASE_10);
    threshold = strtol(argv[3], NULL, BASE_10);
    if (!loops || !num_threads || !threshold) {
        fprintf(stderr, "Usage: ./main <int: loops> <int: threads> <int: threshold>\n");
        return 1;
    }
    else if (num_threads > MAX_THREADS) {
        fprintf(stderr, "Let's not go crazy. Choose %d or less threads.\n", MAX_THREADS);
        return 1;
    }
    printf("Number of threads:\t%d\nNumber of loops:\t%d\nSize of threshold:\t%d\n",
            num_threads, loops, threshold);

    pthread_t threads[num_threads];
    long time[num_threads];
    double total;
    int i, rc;
    scounter_t counter;
    init(&counter, threshold);
    myargs_t args;
    args.loops = loops;
    args.counter = counter;
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
    
    printf("%d threads incrementing a sloppy counter %d times each took %f seconds.\n\n",
            num_threads, loops, total / MILLION);

    return 0;

}

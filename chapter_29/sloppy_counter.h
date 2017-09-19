#include <pthread.h>
#include <limits.h>
#include "wrappers.h"

#define NUMCPUS 8

typedef struct __scounter_t {
    int64_t global;                 // the global total
    pthread_mutex_t glock;          // the global lock
    int local[NUMCPUS];             // the cpu local total
    pthread_mutex_t llock[NUMCPUS]; // the cpu local lock
    int threshold;                  // the max value stored in local, before transfering to global
} scounter_t;

/* init: set threshold, init totals to 0, init locks */
void init(scounter_t *c, int threshold) {
    c->threshold = threshold;
    c->global = 0;
    Pthread_mutex_init(&c->glock, NULL);
    int i;
    for (i = 0; i < NUMCPUS; i++) {
        c->local[i] = 0;
        Pthread_mutex_init(&c->llock[i], NULL);
    }
}

/* update: change the scounter_t value by amt. If the new 
 *      local total >= threshold, transfer to global 
 */
void update(scounter_t *c, int threadID, int amt) {
    int cpu = threadID % NUMCPUS;
    Pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold) {    // transfer local to global
        Pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        Pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    Pthread_mutex_unlock(&c->llock[cpu]);
}

/* get: return the global total. The accuracy is may be off by up to 
 *      NUMCPUS * (threshold - 1) 
 */
int get(scounter_t *c) {
    Pthread_mutex_lock(&c->glock);
    int val = c->global;
    Pthread_mutex_unlock(&c->glock);
    return val;
}

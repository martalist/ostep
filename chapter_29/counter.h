#include "wrappers.h"

typedef struct __counter_t {
    int val;
    pthread_mutex_t lock;
} counter_t;

void counter_init(counter_t *c) {
    c->val = 0;
    Pthread_mutex_init(&c->lock, NULL);
}

void counter_inc(counter_t *c) {
    Pthread_mutex_lock(&c->lock);
    c->val++;
    Pthread_mutex_unlock(&c->lock);
}

void counter_dec(counter_t *c) {
    Pthread_mutex_lock(&c->lock);
    c->val--;
    Pthread_mutex_unlock(&c->lock);
}

int counter_get(counter_t *c) {
    Pthread_mutex_lock(&c->lock);
    int val = c->val;
    Pthread_mutex_unlock(&c->lock);
    return val;
}

int counter_inc_and_get(counter_t *c) {
    Pthread_mutex_lock(&c->lock);
    c->val++;
    int val = c->val;
    Pthread_mutex_unlock(&c->lock);
    return val;
}

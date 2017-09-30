#ifndef __WRAPPERS_h__
#define __WRAPPERS_h__

#include <pthread.h>
#include <assert.h> 
#include <stdlib.h>
#include <sys/time.h>

void Pthread_mutex_init(pthread_mutex_t *m, pthread_mutexattr_t * attr) 
{
    int rc = pthread_mutex_init(m, attr);
    assert(rc == 0);
}

void Pthread_mutex_lock(pthread_mutex_t *m) 
{
    int rc = pthread_mutex_lock(m);
    assert(rc == 0);
}

void Pthread_mutex_unlock(pthread_mutex_t *m) 
{
    int rc = pthread_mutex_unlock(m);
    assert(rc == 0);
}

void Pthread_create(pthread_t *thread, const pthread_attr_t *attr, 	
	       void *(*start_routine)(void*), void *arg)
{
    int rc = pthread_create(thread, attr, start_routine, arg);
    assert(rc == 0);
}

void Pthread_join(pthread_t thread, void **value_ptr)
{
    int rc = pthread_join(thread, value_ptr);
    assert(rc == 0);
}

void *Malloc(size_t size)
{
    void *rc = malloc(size); 
    assert(rc != 0);
    return rc;
}

// void Gettimeofday(struct timeval tp, struct timezone tz) {
    // int rc = gettimeofday(tp, tz);
    // assert(rc == 0);
// }

void Cond_init(pthread_cond_t *__restrict__ cond, const pthread_condattr_t *__restrict__ attr) {
    int rc = pthread_cond_init(cond, attr);
    assert(rc == 0);
}

void Cond_wait(pthread_cond_t *__restrict__ cond, pthread_mutex_t *__restrict__ mutex) {
    int rc = pthread_cond_wait(cond, mutex);
    assert(rc == 0);
}

void Cond_signal(pthread_cond_t *__restrict__ cond) {
    int rc = pthread_cond_signal(cond);
    assert(rc == 0);
}

#endif // __MYTHREADS_h__

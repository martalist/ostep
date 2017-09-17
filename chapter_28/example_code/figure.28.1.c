typedef struct __lock_t { int flag; } lock_t;

void init(lock_t *mutex) {
    mutex->flag = 0;            // 0-> available; 1-> held
}

void lock(lock_t *mutex) {
    while (mutex->flag == 1)    // test the flag
        ;
    mutex->flag = 1;            // now set it
}

void unlock(lock_t *mutex) {
    mutex->flag = 0;
}

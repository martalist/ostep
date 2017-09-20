#include "wrappers.h"

typedef struct __node_t {
    int key;
    struct __node_t *next;
    pthread_mutex_t lock;
} node_t;

typedef struct __llist_t {
    node_t *head;
    pthread_mutex_t lock;
} llist_t;

void ll_init(llist_t *l) {
    Pthread_mutex_init(&l->lock, NULL);
    l->head = NULL;
}

int ll_insert(llist_t *l, int key) {
    node_t *new = malloc(sizeof(node_t));
    if (new == NULL) {    // check malloc success
        return -1;
    } 
    new->key = key;
    Pthread_mutex_init(&new->lock, NULL); 
    Pthread_mutex_lock(&l->lock);   // get llist_t lock
    new->next = l->head;
    l->head = new;
    Pthread_mutex_unlock(&l->lock); // release lock
    return 0;
}

int __ll_indexof_helper(node_t *n, int key, int index) {
    // base cases
    if (n->key == key) {
        Pthread_mutex_unlock(&n->lock); // unlock this node's lock
        return index;
    }
    if (n->next == NULL) {
        Pthread_mutex_unlock(&n->lock); // unlock this node's lock
        return -1;
    }
    // recursive call
    Pthread_mutex_lock(&n->next->lock);
    Pthread_mutex_unlock(&n->lock);     // unlock this node's lock
    return __ll_indexof_helper(n->next, key, ++index);
}

int ll_indexof(llist_t *l, int key) {
    Pthread_mutex_lock(&l->lock);   // get llist_t lock
    if (l->head == NULL) {
        Pthread_mutex_unlock(&l->lock); // release llist_t lock
        return -1;
    }
    node_t *node = l->head;
    Pthread_mutex_lock(&node->lock);   // get head lock
    Pthread_mutex_unlock(&l->lock); // release llist_t lock
    return __ll_indexof_helper(node, key, 0);
}

int ll_length(llist_t *l) {
    int length = 0;
    Pthread_mutex_lock(&l->lock);   // get llist_t lock
    if (l->head == NULL) {
        Pthread_mutex_unlock(&l->lock); // release llist_t lock
        return length;
    }
    node_t *node = l->head;
    Pthread_mutex_lock(&node->lock);   // get head lock
    Pthread_mutex_unlock(&l->lock); // release llist_t lock
    while (node->next != NULL) {
        Pthread_mutex_lock(&node->next->lock);   // get head lock
        Pthread_mutex_unlock(&node->lock); // release llist_t lock
        length++;
    }
    Pthread_mutex_unlock(&node->lock); // release llist_t lock
    return length;
}

#include "counter.h"
#include <pthread.h>

void init_counter(counter_t *c) {
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

int inc_counter(counter_t *c) {
    pthread_mutex_lock(&c->lock);
    int val = ++(c->value);  // Increment and return the new value
    pthread_mutex_unlock(&c->lock);
    return val;
}

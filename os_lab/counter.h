#ifndef COUNTER_H
#define COUNTER_H
#include <pthread.h>

typedef struct {
    int value;
    pthread_mutex_t lock;
} counter_t;

void init_counter(counter_t *c);
int inc_counter(counter_t *c);

#endif // COUNTER_H

#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include <stdint.h>
#include "global.h"

typedef struct {
    uint8_t lock;
} mutex_t;

void get_mutex(mutex_t mutex);
void release_mutex(mutex_t mutex);

#endif // SEMAPHORE_H
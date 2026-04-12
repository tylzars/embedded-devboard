#include <stdint.h>
#include "global.h"
#include "mutex.h"

// Neither of these are atomic :(
// TODO: Add to Makefile
// TODO: Make atomic
// TODO: :painguin:
void get_mutex(mutex_t mutex) {
    while (mutex.lock == true) {};
    mutex.lock = true;
    return;
}

void release_mutex(mutex_t mutex) {
    mutex.lock = false;
    return;
}
#include "timer.h"

void enable_timer(uint8_t timer) {
    if (timer > 7) {
        // Not a valid timer
        return;
    }
    SET_BIT(SYSCTL_RCGCTIMER, 1 << timer);
}

void disable_timer(uint8_t timer) {
    if (timer > 7) {
        // Not a valid timer
        return;
    }
    UNSET_BIT(SYSCTL_RCGCTIMER, 1 << timer);
}
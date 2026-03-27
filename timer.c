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

// 13.4.1
void enable_timer_0(void) {
    UNSET_BIT(TIMER0_GPTMCTL, 1 << 0);
    TIMER0_GPTMCFG = 0x0;
    SET_BIT(TIMER0_GPTMTAMR, 1);
    TIMER0_GPTMTAILR = (uint16_t)10;
    SET_BIT(TIMER0_GPTMIMR, 1 << 0); 
    SET_BIT(TIMER0_GPTMCTL, 1 << 0);
}
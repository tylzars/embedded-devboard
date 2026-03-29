#include "timer.h"

void enable_timer(uint8_t timer) {
    if (timer > 7) {
        // Not a valid timer
        return;
    }
    // Disable timer on first boot
    UNSET_BIT(TIMER0->GPTMCTL, 1 << 0); // TODO: Unhardcode this
    // Enable
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
void start_timer(timer_t *timer, uint16_t time) {
    UNSET_BIT(timer->GPTMCTL, 1 << 0);
    timer->GPTMCFG = 0x0;
    SET_BIT(timer->GPTMTAMR, 1);
    timer->GPTMTAILR = (uint16_t)time;
    SET_BIT(timer->GPTMIMR, 1 << 0); 
    SET_BIT(timer->GPTMCTL, 1 << 0);
}
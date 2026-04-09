#include "timer.h"

// Variables
bool volatile timer0_triggered = false;

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
void start_timer(timer_t *timer, uint32_t time) {
    UNSET_BIT(timer->GPTMCTL, BIT(0));
    timer->GPTMCFG = 0x0;
    SET_BIT(timer->GPTMTAMR, 1);
    timer->GPTMTAILR = (uint32_t)time;
    SET_BIT(timer->GPTMIMR, BIT(0)); 
    SET_BIT(timer->GPTMCTL, BIT(0));
}

void isr_timer0(void) {
    SET_BIT(TIMER0->GPTMICR, BIT(0));
    timer0_triggered = true; // Don't update display here to keep this quick
    return;
}
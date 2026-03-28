#include "timer.h"

void enable_timer(uint8_t timer) {
    if (timer > 7) {
        // Not a valid timer
        return;
    }
    // Disable timer on first boot
    UNSET_BIT(*(volatile uint32_t*)(TIMER0_BASE + GPTMCTL), 1 << 0);
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
void enable_timer_0(void) {
    UNSET_BIT(*(volatile uint32_t*)(TIMER0_BASE + GPTMCTL), 1 << 0);
    *(volatile uint32_t*)(TIMER0_BASE + GPTMCFG) = 0x0;
    SET_BIT(*(volatile uint32_t*)(TIMER0_BASE + GPTMTAMR), 1);
    *(volatile uint32_t*)(TIMER0_BASE + GPTMTAILR) = (uint16_t)10;
    SET_BIT(*(volatile uint32_t*)(TIMER0_BASE + GPTMIMR), 1 << 0); 
    SET_BIT(*(volatile uint32_t*)(TIMER0_BASE + GPTMCTL), 1 << 0);
}
#ifndef TIMER_H
#define TIMER_H

#include <stdint.h>
#include "global.h"

#define SYSCTL_RCGCTIMER (*(volatile uint32_t *)0x400FE604)

#define TIMER0_BASE 0x40030000
#define TIMER1_BASE 0x40031000
#define TIMER2_BASE 0x40032000
#define TIMER3_BASE 0x40033000
#define TIMER4_BASE 0x40034000
#define TIMER5_BASE 0x40035000
#define TIMER6_BASE 0x400E0000
#define TIMER7_BASE 0x400E1000

#define GPTMCFG      0x000
#define GPTMTAMR     0x004
#define GPTMTBMR     0x008
#define GPTMCTL      0x00C
#define GPTMIMR      0x018
#define GPTMIRS      0x01C
#define GPTMICR      0x024
#define GPTMTAILR    0x028
#define GPTMTBILR    0x02C

#define TIMER0 (1 << 0)
#define TIMER1 (1 << 1)
#define TIMER2 (1 << 2)
#define TIMER3 (1 << 3)
#define TIMER4 (1 << 4)
#define TIMER5 (1 << 5)
#define TIMER6 (1 << 6)
#define TIMER7 (1 << 7)

// Functionality
void enable_timer(uint8_t timer);
void disable_timer(uint8_t timer);
void enable_timer_0(void);

#endif // TIMER_H
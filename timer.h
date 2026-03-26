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

#define TIMER0_GPTMCFG      (*(volatile uint32_t*)(TIMER0_BASE + 0x000))
#define TIMER0_GPTMTAMR     (*(volatile uint32_t*)(TIMER0_BASE + 0x004))
#define TIMER0_GPTMTBMR     (*(volatile uint32_t*)(TIMER0_BASE + 0x008))
#define TIMER0_GPTMCTL      (*(volatile uint32_t*)(TIMER0_BASE + 0x00C))
#define TIMER0_GPTMIMR      (*(volatile uint32_t*)(TIMER0_BASE + 0x018))
#define TIMER0_GPTMIRS      (*(volatile uint32_t*)(TIMER0_BASE + 0x01C))
#define TIMER0_GPTMICR      (*(volatile uint32_t*)(TIMER0_BASE + 0x024))
#define TIMER0_GPTMTAILR    (*(volatile uint32_t*)(TIMER0_BASE + 0x028))
#define TIMER0_GPTMTBILR    (*(volatile uint32_t*)(TIMER0_BASE + 0x02C))

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
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

typedef struct {
    __IOM uint32_t GPTMCFG;
    __IOM uint32_t GPTMTAMR; 
    __IOM uint32_t GPTMTBMR;
    __IOM uint32_t GPTMCTL;
    __IOM uint32_t GPTMSYNC;
    __IOM uint32_t RESERVED1;
    __IOM uint32_t GPTMIMR;
    __IOM uint32_t GPTMIRS;
    __IOM uint32_t GPTMMIS;
    __IOM uint32_t GPTMICR;
    __IOM uint32_t GPTMTAILR;
    __IOM uint32_t GPTMTBILR;
} timer_t;

#define TIMER0 ((timer_t*)TIMER0_BASE)
#define TIMER1 ((timer_t*)TIMER1_BASE)
#define TIMER2 ((timer_t*)TIMER2_BASE)
#define TIMER3 ((timer_t*)TIMER3_BASE)
#define TIMER4 ((timer_t*)TIMER4_BASE)
#define TIMER5 ((timer_t*)TIMER5_BASE)
#define TIMER6 ((timer_t*)TIMER6_BASE)
#define TIMER7 ((timer_t*)TIMER7_BASE)

// Functionality
void enable_timer(uint8_t timer);
void disable_timer(uint8_t timer);
void start_timer(timer_t *timer, uint32_t time);
void isr_timer0(void);

#endif // TIMER_H
#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include "global.h"

// Address Definitions
#define HIB_BASE_ADDR 0x400FC000
#define HIBRTCC     (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x0))
#define HIBRTCLD    (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x8))
#define HIBCTL      (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x10))
#define HIBIM       (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x14))
#define HIBMIS      (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x1C))
#define HIBRTCSS    (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x28))

// Bit Definitions
#define RTCEN 0x1

// Functionality
void enable_hibernation(void);
void enable_rtc(void);
int16_t rtc_read_subseconds(void);
int32_t rtc_read_seconds(void);
void sleep_s(int32_t seconds);

#endif // RTC_H
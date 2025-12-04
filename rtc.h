#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include "global.h"


#define HIB_BASE_ADDR 0x400FC000
#define HIBCTL      (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x10))
#define HIBRTCC     (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x0))
#define HIBRTCSS    (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x28))
#define HIBRTCLD    (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x8))
#define HIBIM       (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x14))
#define HIBMIS      (*(volatile uint32_t*)(HIB_BASE_ADDR + 0x1C))

void enable_hibernation();
void enable_rtc();
int16_t rtc_read();

#endif // RTC_H


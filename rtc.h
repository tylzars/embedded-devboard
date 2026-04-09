#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include "global.h"

// Address Definitions
#define HIB_BASE_ADDR 0x400FC000

typedef struct {
    __IM uint32_t HIBRTCC;
    __IOM uint32_t HIBRTCM0;
    __IM uint8_t reserved[4];
    __OM uint32_t HIBRTCLD;     // WO
    __IOM uint32_t HIBCTL;
    __IOM uint32_t HIBIM;
    __IM uint32_t HIBRIS;
    __IM uint32_t HIBMIS;
    __IOM uint32_t HIBIC;        // RW1C
    __IOM uint32_t HIBRTCT;
    __IOM uint32_t HIBRTCSS;
    __IOM uint32_t HIBIO;
    // TODO: Finish
} hib_t;

#define HIB ((hib_t*)HIB_BASE_ADDR)

// Bit Definitions
#define RTCEN BIT(1)

// Functionality
void enable_hibernation(void);
void enable_rtc(void);
int16_t rtc_read_subseconds(void);
int32_t rtc_read_milliseconds(void);
int32_t rtc_read_seconds(void);
void sleep_s(int32_t seconds);
void sleep_ms(int16_t milliseconds);

#endif // RTC_H
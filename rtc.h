#ifndef RTC_H
#define RTC_H

#include <stdint.h>
#include "global.h"

// Address Definitions
#define HIB_BASE_ADDR 0x400FC000

typedef struct {
    const volatile uint32_t HIBRTCC;
    volatile uint32_t HIBRTCM0;
    uint8_t reserved[4];
    volatile uint32_t HIBRTCLD; // WO
    volatile uint32_t HIBCTL;
    volatile uint32_t HIBIM;
    const volatile uint32_t HIBRIS;
    const volatile uint32_t HIBMIS;
    volatile uint32_t HIBIC;        // What does RW1C mean?
    volatile uint32_t HIBRTCT;
    volatile uint32_t HIBRTCSS;
    volatile uint32_t HIBIO;
    // TODO: Finish
} hib_t;

#define HIB ((hib_t*)HIB_BASE_ADDR)

// Bit Definitions
#define RTCEN 0x1

// Functionality
void enable_hibernation(void);
void enable_rtc(void);
int16_t rtc_read_subseconds(void);
int32_t rtc_read_milliseconds(void);
int32_t rtc_read_seconds(void);
void sleep_s(int32_t seconds);
void sleep_ms(int16_t milliseconds);

#endif // RTC_H
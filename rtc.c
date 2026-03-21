#include <stdint.h>
#include "rtc.h"
#include "global.h"

// 7.4.1
void enable_hibernation(void) {   
    // Enable WC interrupt
    HIBIM = (int32_t)0x10;
    // Wait for HIBCTL to be writable
    while((HIBCTL & 0x80000000) == 0);
    // Enable oscillator input
    HIBCTL = (int32_t)0x40;
    // Wait for WC interrupt to trigger
    while((HIBMIS & 0x10) == 0);
}

// 7.3.5.1
void enable_rtc(void) {
    // Wait for register to be writable
    while((HIBCTL & 0x80000000) == 0);
    // Enable RTC
    SET_BIT(HIBCTL, 0x1); // Make this a #define
}

int16_t rtc_read_subseconds(void) {
    int32_t pre_read_val = HIBRTCC;

    int16_t read_val = HIBRTCSS & 0x7FFF;

    int32_t post_read_val = HIBRTCC;

    if (post_read_val != pre_read_val) {
        return -1;
    } else {
        return read_val;
    }
}

int32_t rtc_read_seconds(void) {
    return HIBRTCC;
}

void sleep_s(int32_t seconds) {
    int32_t init_time = HIBRTCC;
    while (HIBRTCC < init_time + seconds);
}
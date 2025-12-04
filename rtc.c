#include <stdint.h>
#include "rtc.h"
#include "global.h"

void enable_hibernation() {
    // 7.4.1 / 7.4.2
    HIBIM = (int32_t)0x10;
    HIBCTL =  (int32_t)0x40;
    while((HIBMIS & 0x10) == 0);
    // skip step 2
    HIBRTCLD = (int32_t)0x0;
    // skip step 4
    HIBCTL =  (int32_t)0x41;

}

void enable_rtc() {
    SET_BIT(HIBCTL, 0x1);
}

int16_t rtc_read() {
    int32_t pre_read_val = HIBRTCC;

    int16_t read_val = HIBRTCSS & 0x7FFF;

    int32_t post_read_val = HIBRTCC;

    if (post_read_val != pre_read_val) {
        return -1;
    } else {
        return read_val;
    }
}

#include <stdint.h>
#include "lcd.h"

char nibble_to_printable_hex(uint8_t nibble) {
    if (nibble < 10) {
        // Handle case where 0-9
        // 0x1 + 0x30 = 0x31 (0)
        nibble = nibble + '0';
    } else {
        // Handle case where a-f
        // 0xA + 0x41 = 0x4B (K)
        // 0x4B - 0xA = 0x41 (A)
        nibble = nibble + 'A' - 10;
    }

    return nibble;
}

void byte_to_printable_hex(uint16_t byte) {
    char tmp[2];
    tmp[0] = nibble_to_printable_hex(byte >> 4);
    tmp[1] = nibble_to_printable_hex(byte & 0xf);

    lcd_put_string(tmp);
}
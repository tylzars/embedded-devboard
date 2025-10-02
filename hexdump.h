#ifndef hexdump
#define hexdump

#include <stdint.h>
#include "lcd.h"

char nibble_to_printable_hex(uint8_t nibble);
void byte_to_printable_hex(uint16_t byte);

#endif
#ifndef hexdump
#define hexdump

#include <stdint.h>
#include "lcd.h"

// Functionality
char nibble_to_printable_hex(uint8_t nibble);
void byte_to_printable_hex(uint8_t byte);

#endif
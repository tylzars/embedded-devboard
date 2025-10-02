#include <stdint.h>
#include "hexdump.h"
#include "global.h"
#include "lcd.h"

int main() {
    delay_ms(20);
    init_screen();
    lcd_set_display_on_off(true, false, true);
    lcd_set_entry_mode(true, false);

    bool test = false;
    int64_t loop = 0;

    while(true) {
        if (test) {
            lcd_put_string("It works!");
            lcd_move_cursor(0x1, 0xB);
            lcd_put_string("Cool!");
        }

        for (int i = 0; i < 8; i++) {
            byte_to_printable_hex(*(uint8_t*)(loop+i));
        }
        

        delay_ms(1000);
        lcd_clear_screen();
        delay_ms(1000);
        loop += 8;
    }

    return 0;
}
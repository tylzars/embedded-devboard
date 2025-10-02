#include <stdint.h>
#include "hexdump.h"
#include "global.h"
#include "lcd.h"

int main() {
    delay_ms(20);
    init_screen();
    lcd_set_display_on_off(true, false, true);
    lcd_set_entry_mode(true, false);

    while(1) {
        lcd_move_cursor(0x0, 0xB);
        lcd_put_string("Wow!");
        lcd_return_cursor_home();
        lcd_put_string("It works!");
        lcd_move_cursor(0x1, 0xB);
        lcd_put_string("Cool!");

        byte_to_printable_hex(0xAF);

        delay_ms(1000);
        lcd_clear_screen();
        delay_ms(1000);
    }

    return 0;
}
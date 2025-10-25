#include <stdint.h>
#include "hexdump.h"
#include "global.h"
#include "lcd.h"
#include "mlib.h"

int main() {
    delay_ms(20);
    init_screen();
    lcd_set_display_on_off(true, false, true);
    lcd_set_entry_mode(true, false);

    bool test = false;
    int32_t loop = 0;

    while(true) {
        if (test) {
            lcd_put_string("It works!");
            lcd_move_cursor(0x1, 0xB);
            lcd_put_string("Cool!");
        }

        char curr_addr[10] = {0};
        //itoa(loop, curr_addr);
        char hex_curr_addr[10] = "0x"; // this isn't even a hex number...
        itohs(loop, curr_addr);
        m_strcat(hex_curr_addr, curr_addr);
        lcd_put_string(hex_curr_addr);
        lcd_move_cursor(0x1, 0x8);

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
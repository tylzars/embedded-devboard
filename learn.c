#include <stdint.h>
#include "hexdump.h"
#include "global.h"
#include "lcd.h"
#include "mlib.h"
#include "rtc.h"

int main() {
    delay_ms(20);
    init_screen();
    lcd_set_display_on_off(true, false, true);
    lcd_set_entry_mode(true, false);

    enable_hibernation();
    enable_rtc();

    bool test = false;
    int32_t loop = 0;

    while(true) {
        if (test) {
            lcd_put_string("It works!");
            lcd_move_cursor(0x1, 0xB);
            lcd_put_string("Cool!");
        }

        // char rtc_readd[10] = {0};
        // itoa(rtc_read(), rtc_readd);
        // lcd_put_string(rtc_readd);
        // delay_ms(500);

        char hex_curr_addr[10];
        m_memset(hex_curr_addr, 0, 10);
        m_sprintf(hex_curr_addr, "%X", loop);
        lcd_put_string(hex_curr_addr);
        lcd_move_cursor(0x1, 0x8);

        for (int i = 0; i < 8; i++) {
            byte_to_printable_hex(*(uint8_t*)(loop+i));
        }
        

        delay_ms(1000);
        lcd_clear_screen();
        loop += 8;
    }

    return 0;
}
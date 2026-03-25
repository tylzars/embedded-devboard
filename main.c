#include <stdint.h>
#include "hexdump.h"
#include "global.h"
#include "lcd.h"
#include "mlib.h"
#include "rtc.h"
#include "seven_seg.h"
#include "timer.h"

int main() {
    // TODO: Move all INIT code into one file (maybe bootloader?)
    delay_ms(20);
    lcd_init();
    lcd_set_display_on_off(true, false, true);
    lcd_set_entry_mode(true, false);

    enable_hibernation();
    enable_rtc();

    seven_seg_init();
    seven_seg_blank();
    delay_ms(1000);
    seven_seg_show_hex(0x33);
    seven_seg_set_decimal_points(false, true);

    enable_timer(0);
      
    int32_t loop = 0;
    char line_buffer[16];

    while(true) {
        // RTC Test Code
        char rtc_readd[10] = {0};
        itoa(rtc_read_seconds(), rtc_readd);
        lcd_put_string(rtc_readd);
        sleep_s(5);
        itoa(rtc_read_seconds(), rtc_readd);
        lcd_move_cursor(0x1, 0);
        lcd_put_string(rtc_readd);
        sleep_s(2);
        lcd_clear_screen();
        
        // LCD Hexdump
        m_memset(line_buffer, 0, 16);
        m_sprintf(line_buffer, "%X\n", loop);
        lcd_put_string(line_buffer);

        for (int i = 0; i < 8; i++) {
            byte_to_printable_hex(*(uint8_t*)(loop+i));
        }
        

        sleep_s(2);
        lcd_clear_screen();
        loop += 8;
    }

    return 0;
}
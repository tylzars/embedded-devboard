#include <stdint.h>
#include "global.h"
#include "lcd.h"
#include "mlib.h"
#include "rtc.h"
#include "seven_seg.h"
#include "timer.h"

int main() {
    // TODO: Move all INIT code into one file (maybe bootloader?)
    enable_hibernation();
    enable_rtc();

    delay_ms(20);
    lcd_init();
    lcd_set_display_on_off(true, false, true);
    lcd_set_entry_mode(true, false);

    seven_seg_init();
    seven_seg_blank();
    sleep_s(1);
    seven_seg_show_hex(0x33);
    seven_seg_set_decimal_points(false, true);

    // Enable systick
    // 1. Program the value in the STRELOAD register.
    // 2. Clear the STCURRENT register by writing to it with any value.
    // 3. Configure the STCTRL register for the required operation.
    SYSTICK->STRELOAD = 0x00FFFFFF;
    SYSTICK->STCURRENT = 0x00FFFFFF;
    SET_BIT(SYSTICK->STCTRL, BIT(0) | BIT(1));

    // NVIC Enables (3.4)
    if ((NVIC->isr_en0 & (1 << 19)) == 0) {
        SET_BIT(NVIC->isr_en0, TIMER0_ISR);    
    }

    enable_timer(0);
      
    int32_t loop = 0xe000e100;
    char line_buffer[16];

    while(true) {
        // LCD Hexdump
        m_memset(line_buffer, 0, 16);
        m_sprintf(line_buffer, "%X\n", loop);
        lcd_put_string(line_buffer);
        
        char tmp[17] = "\0";
        char* p = tmp;
        for (int i = 0; i < 8; i+=4) {
            p += m_sprintf(p, "%x", *(uint32_t*)(loop+i));
        }
        *p = '\0';
        lcd_put_string(tmp);
        
        
        seven_seg_set_decimal_points(false, true);
        
        // Let timer rip
        start_timer(TIMER0, 32000000);

        // Check if timer finished
        extern bool timer0_triggered;
        if(timer0_triggered) {
            seven_seg_show_hex((((loop - 0xe000e100) & 0xFF) % 0xFF));
            timer0_triggered = false;
        }

        sleep_s(5);

        lcd_clear_screen();
        loop += 8;
    }

    return 0;
}
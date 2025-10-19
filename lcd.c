#include <stdint.h>
#include "global.h"
#include "lcd.h"

// Helper Functions
void delay_ms(int ms) {
    volatile int i, j;
    for(i = 0; i < ms; i++) {
        for(j = 0; j < 3000; j++);  // Inner loop calibrated for ~1ms
    }
}

void delay_us(int us) {
    volatile int i;
    for(i = 0; i < us * 120; i++);  // Loop calibrated for ~1μs per iteration
}

void toggle_lcd_enable() {
    // Toggle E on and off
    delay_us(1);
    SET_BIT(GPIO_N_DATA, LCD_E);
    delay_us(1);
    UNSET_BIT(GPIO_N_DATA, LCD_E);
    delay_us(50);
}

void clear_data_lines() {
    UNSET_BIT(GPIO_M_DATA, LCD_D4);
    UNSET_BIT(GPIO_M_DATA, LCD_D5);
    UNSET_BIT(GPIO_M_DATA, LCD_D6);
    UNSET_BIT(GPIO_M_DATA, LCD_D7);
}

// Worker Functions
int init_screen() {
    SET_BIT(SYSCTL_GPIOHBCTL, 0x1800);  // Enable AHB for ports M and N
    SET_BIT(SYSCTL_RCGCGPIO, 0x1800);   // Enable clocks for ports M and N
    delay_ms(10);

    // Set registers to output on these bits (pins) [by setting register to 1]
    SET_BIT(GPIO_N_DIR, LCD_E | LCD_RS);
    SET_BIT(GPIO_M_DIR, LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7);

    // Set GPIO Digital Enable bits (pins)  [by setting register to 1]
    SET_BIT(GPIO_N_DEN, LCD_E | LCD_RS);
    SET_BIT(GPIO_M_DEN, LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7);

    // Initialize all LCD pins to logic low (idle state)
    // RS=0 (command mode), E=0 (not enabled), all data lines=0
    UNSET_BIT(GPIO_N_DATA, (LCD_RS | LCD_E));
    UNSET_BIT(GPIO_M_DATA, (LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7));

    delay_ms(50);

    // Toggle RS
    UNSET_BIT(GPIO_N_DATA, LCD_RS);

    // Function set (do it 3 times)
    for (int i = 0; i < 3; i++){ 
        UNSET_BIT(GPIO_N_DATA, LCD_E);
        SET_BIT(GPIO_M_DATA, LCD_D4);
        SET_BIT(GPIO_M_DATA, LCD_D5);
        UNSET_BIT(GPIO_M_DATA, LCD_D6);
        UNSET_BIT(GPIO_M_DATA, LCD_D7);
        toggle_lcd_enable();

        if (i == 0) {
            delay_ms(5);
        } else {
            delay_us(150);
        }
    }

    // Set interface to be 4 bits long
    UNSET_BIT(GPIO_N_DATA, LCD_E);
    UNSET_BIT(GPIO_M_DATA, LCD_D4);
    SET_BIT(GPIO_M_DATA, LCD_D5);
    UNSET_BIT(GPIO_M_DATA, LCD_D6);
    UNSET_BIT(GPIO_M_DATA, LCD_D7);
    toggle_lcd_enable();
    clear_data_lines();

    // Lines Set (0x28) >> 0x2
    UNSET_BIT(GPIO_N_DATA, LCD_E);
    UNSET_BIT(GPIO_M_DATA, LCD_D4);
    SET_BIT(GPIO_M_DATA, LCD_D5);
    UNSET_BIT(GPIO_M_DATA, LCD_D6);
    UNSET_BIT(GPIO_M_DATA, LCD_D7);
    toggle_lcd_enable();

    // Lines Set (0x28) >> 0x8
    UNSET_BIT(GPIO_N_DATA, LCD_E);
    UNSET_BIT(GPIO_M_DATA, LCD_D4);
    UNSET_BIT(GPIO_M_DATA, LCD_D5);
    UNSET_BIT(GPIO_M_DATA, LCD_D6);
    SET_BIT(GPIO_M_DATA, LCD_D7);
    toggle_lcd_enable();
    clear_data_lines();

    // Display/Cursor Set (0x0C) >> 0x0
    UNSET_BIT(GPIO_N_DATA, LCD_E);
    UNSET_BIT(GPIO_M_DATA, LCD_D4);
    UNSET_BIT(GPIO_M_DATA, LCD_D5);    
    UNSET_BIT(GPIO_M_DATA, LCD_D6);      
    UNSET_BIT(GPIO_M_DATA, LCD_D7);
    toggle_lcd_enable();

    // Display/Cursor Set (0x0C) >> 0xC
    UNSET_BIT(GPIO_N_DATA, LCD_E);
    UNSET_BIT(GPIO_M_DATA, LCD_D4);
    UNSET_BIT(GPIO_M_DATA, LCD_D5);    
    SET_BIT(GPIO_M_DATA, LCD_D6);      
    SET_BIT(GPIO_M_DATA, LCD_D7);
    toggle_lcd_enable();
    clear_data_lines();

    // Display/Cursor Shift (0x06) >> 0x0
    UNSET_BIT(GPIO_N_DATA, LCD_E);
    UNSET_BIT(GPIO_M_DATA, LCD_D4);
    UNSET_BIT(GPIO_M_DATA, LCD_D5);    
    UNSET_BIT(GPIO_M_DATA, LCD_D6);      
    UNSET_BIT(GPIO_M_DATA, LCD_D7);
    toggle_lcd_enable();

    // Display/Cursor Shift (0x06) >> 0x6
    UNSET_BIT(GPIO_N_DATA, LCD_E);
    UNSET_BIT(GPIO_M_DATA, LCD_D4);
    SET_BIT(GPIO_M_DATA, LCD_D5);    
    SET_BIT(GPIO_M_DATA, LCD_D6);      
    UNSET_BIT(GPIO_M_DATA, LCD_D7);
    toggle_lcd_enable();
    clear_data_lines();

    // Display/Cursor Shift (0x01) >> 0x0
    UNSET_BIT(GPIO_N_DATA, LCD_E);
    UNSET_BIT(GPIO_M_DATA, LCD_D4);
    UNSET_BIT(GPIO_M_DATA, LCD_D5);    
    UNSET_BIT(GPIO_M_DATA, LCD_D6);      
    UNSET_BIT(GPIO_M_DATA, LCD_D7);
    toggle_lcd_enable();

    // Display/Cursor Shift (0x01) >> 0x1
    UNSET_BIT(GPIO_N_DATA, LCD_E);
    SET_BIT(GPIO_M_DATA, LCD_D4);
    UNSET_BIT(GPIO_M_DATA, LCD_D5);    
    UNSET_BIT(GPIO_M_DATA, LCD_D6);      
    UNSET_BIT(GPIO_M_DATA, LCD_D7);
    toggle_lcd_enable();
    clear_data_lines();

    delay_ms(2);

    return 0;
}

void lcd_put_char(char c) {
    // Setup RS for data
    SET_BIT(GPIO_N_DATA, LCD_RS);
    
    // Clear all data lines first for clean state
    clear_data_lines();

    /*
     * Send upper nibble of 'A' (0x41 >> 4 = 0x4)
     * 0x4 = 0100 binary, so we need:
     * LCD_D4 = 0, LCD_D5 = 0, LCD_D6 = 1, LCD_D7 = 0
    */
    
    // Calcuate only upper nibble
    char tmp = c >> 4;

    // Check bits in upper nibble
    if (tmp & 0x1) {
        SET_BIT(GPIO_M_DATA, LCD_D4); 
    } 
    if (tmp & 0x2) {
        SET_BIT(GPIO_M_DATA, LCD_D5);
    } 
    if (tmp & 0x4){
        SET_BIT(GPIO_M_DATA, LCD_D6);
    } 
    if (tmp & 0x8) {
        SET_BIT(GPIO_M_DATA, LCD_D7);
    }
    
    // Latch upper nibble
    toggle_lcd_enable();
    
    /*
     * Send lower nibble of 'A' cl
     * 0x1 = 0001 binary, so we need:
     * LCD_D4 = 1, LCD_D5 = 0, LCD_D6 = 0, LCD_D7 = 0
     */
    
    // Clear all data lines first
    clear_data_lines();
    
    // Calcuate only lower nibble
    tmp = c & 0xf;

    // Check bits in lower nibble
    if (tmp & 0x1) {
        SET_BIT(GPIO_M_DATA, LCD_D4); 
    } 
    if (tmp & 0x2) {
        SET_BIT(GPIO_M_DATA, LCD_D5);
    } 
    if (tmp & 0x4){
        SET_BIT(GPIO_M_DATA, LCD_D6);
    } 
    if (tmp & 0x8) {
        SET_BIT(GPIO_M_DATA, LCD_D7);
    }
    
    // Latch lower nibble
    toggle_lcd_enable();
    
    // Character write completion delay
    delay_us(50);
}

void lcd_clear_screen() {
    //               RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
    // Clear Display 0  0   0   0   0   0   0   0   0   1 
    
    // Setup RS for command
    UNSET_BIT(GPIO_N_DATA, LCD_RS);
    
    // Unset top half
    clear_data_lines();
    toggle_lcd_enable();

    // Unset bottom half
    clear_data_lines();
    SET_BIT(GPIO_M_DATA, LCD_D4); // Set last bottom bit
    toggle_lcd_enable();
}

void lcd_return_cursor_home() {
    //               RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
    // Return Home   0  0   0   0   0   0   0   0   1   -

    // Setup RS for command
    UNSET_BIT(GPIO_N_DATA, LCD_RS);

    // Set upper
    clear_data_lines();
    toggle_lcd_enable();

    // Set lower
    clear_data_lines();
    SET_BIT(GPIO_M_DATA, LCD_D5);
    toggle_lcd_enable();
}

void lcd_put_string(char* string) {
    int i = 0;
    while(string[i] != 0x0) {
        lcd_put_char(string[i]);
        i++;
    }
}

// Row 0 = Top, Row 1 = Bottom
// TODO: How column works
void lcd_move_cursor(uint8_t row, uint8_t col) {
    //             RS R/W DB7 DB6 DB5 DB4 DB3 DB2 DB1 DB0
    // Set DDRAM   0  0   1   AC6 AC5 AC4 AC3 AC2 AC1 AC0

    // Setup RS for command
    UNSET_BIT(GPIO_N_DATA, LCD_RS);

    if (row >=2 || col >= 16) {
        return;
    }

    // Handle 2nd row offset
    if (row == 1) {
        row += 0x41;
    }

    // Top half
    clear_data_lines();
    SET_BIT(GPIO_M_DATA, LCD_D7); // Always 1
    if (row & 0x1) {
        SET_BIT(GPIO_M_DATA, LCD_D4); 
    } 
    if (row & 0x2) {
        SET_BIT(GPIO_M_DATA, LCD_D5);
    } 
    if (row & 0x4){
        SET_BIT(GPIO_M_DATA, LCD_D6);
    } 
    toggle_lcd_enable();

    // Bottom half
    clear_data_lines();
    if (col & 0x1) {
        SET_BIT(GPIO_M_DATA, LCD_D4); 
    } 
    if (col & 0x2) {
        SET_BIT(GPIO_M_DATA, LCD_D5);
    } 
    if (col & 0x4){
        SET_BIT(GPIO_M_DATA, LCD_D6);
    } 
    if (col & 0x8) {
        SET_BIT(GPIO_M_DATA, LCD_D7);
    }
    toggle_lcd_enable();
}

void lcd_set_display_on_off(bool display, bool cursor, bool blinking) {
    // Setup RS for command
    UNSET_BIT(GPIO_N_DATA, LCD_RS);

    // Clear upper
    clear_data_lines();
    toggle_lcd_enable();

    // Set lower
    clear_data_lines();
    SET_BIT(GPIO_M_DATA, LCD_D7);
    if (display) {
        SET_BIT(GPIO_M_DATA, LCD_D6);
    }
    if (cursor) {
        SET_BIT(GPIO_M_DATA, LCD_D5);
    }
    if (blinking) {
        SET_BIT(GPIO_M_DATA, LCD_D4);
    }
    toggle_lcd_enable();
}

void lcd_set_entry_mode(bool cursor_direction, bool enable_shift) {
    UNSET_BIT(GPIO_N_DATA, LCD_RS);
    clear_data_lines();
    toggle_lcd_enable();

    clear_data_lines();
    SET_BIT(GPIO_M_DATA, LCD_D6);
   
    // true is right | false is left
    if (cursor_direction) {
        SET_BIT(GPIO_M_DATA, LCD_D5);
    }
    if (enable_shift) {
        SET_BIT(GPIO_M_DATA, LCD_D4);
    }
    toggle_lcd_enable();
}
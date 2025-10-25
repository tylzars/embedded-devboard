#ifndef LCD_H
#define LCD_H

#include <stdint.h>
#include "global.h"

// System Control (TI Specifics)
#define SYSCTL_RCGCGPIO  (*(volatile uint32_t *)0x400FE608)
#define SYSCTL_GPIOHBCTL (*(volatile uint32_t *)0x400FE06C)

// GPIO Base
#define GPIO_M_BASE 0x40063000 // LCD 4-7
#define GPIO_N_BASE 0x40064000 // RST / E

// GPIO Data
#define GPIO_N_DATA (*(volatile unsigned long *)(GPIO_N_BASE + 0x3FC))
#define GPIO_M_DATA (*(volatile unsigned long *)(GPIO_M_BASE + 0x3FC))

// Direction Registers
#define GPIO_N_DIR (*(volatile unsigned long *)(GPIO_N_BASE + 0x400))
#define GPIO_M_DIR (*(volatile unsigned long *)(GPIO_M_BASE + 0x400))

// GPIO Interrupt Sense (GPIOIS)
#define GPIO_N_GPIOIS (*(volatile unsigned long *)(GPIO_N_BASE + 0x404))
#define GPIO_M_GPIOIS (*(volatile unsigned long *)(GPIO_M_BASE + 0x404))

// GPIO Digital Enable
#define GPIO_N_DEN (*(volatile unsigned long *)(GPIO_N_BASE + 0x51C))
#define GPIO_M_DEN (*(volatile unsigned long *)(GPIO_M_BASE + 0x51C))

// LCD Data Bits
#define LCD_D4   0x10   // PM4 (bit 4) - Data line 4 (LSB in 4-bit mode)
#define LCD_D5   0x20   // PM5 (bit 5) - Data line 5
#define LCD_D6   0x40   // PM6 (bit 6) - Data line 6
#define LCD_D7   0x80   // PM7 (bit 7) - Data line 7 (MSB in 4-bit mode)

// LCD Control Bits
#define LCD_RS   0x01   // PN0 (bit 0) - Register Select: 0=Command, 1=Data
#define LCD_E    0x02   // PN1 (bit 1) - Enable: Rising edge latches data/commands

// Timing Functions
void delay_ms(int ms);
void delay_us(int us);

// LCD Initialization
int init_screen(void);

// LCD Basic Operations
void lcd_put_char(char c);
void lcd_put_string(char* string);
void lcd_clear_screen(void);
void lcd_return_cursor_home(void);
void lcd_move_cursor(uint8_t row, uint8_t col);

// LCD Configuration
void lcd_set_display_on_off(bool display, bool cursor, bool blinking);
void lcd_set_entry_mode(bool cursor_direction, bool enable_shift);

#endif // LCD_H
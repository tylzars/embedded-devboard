#include <stdint.h>

// System Control (TI Specifics)
#define SYSCTL_RCGCGPIO  (*(volatile uint32_t *)0x400FE608)
#define SYSCTL_GPIOHBCTL (*(volatile uint32_t *)0x400FE06C)

// GPIO Base
#define GPIO_M_BASE 0x40063000 // LCD 4-7
#define GPIO_N_BASE 0x40064000 // RST / E

// GPIO Data
// I still have no fucking idea how cluade managed to pull this 0x3FC shit out of its ass...
#define GPIO_N_DATA (*(volatile unsigned long *)(GPIO_N_BASE + 0x3FC))
#define GPIO_M_DATA (*(volatile unsigned long *)(GPIO_M_BASE + 0x3FC))

// Direction Registers
#define GPIO_N_DIR (*(volatile unsigned long *)(GPIO_N_BASE + 0x400))
#define GPIO_M_DIR (*(volatile unsigned long *)(GPIO_M_BASE + 0x400))

// GPIO Interrupt Sense (GPIOIS)
#define GPIO_N_GPIOIS (*(volatile unsigned long *)(GPIO_N_BASE + 0x404))
#define GPIO_M_GPIOIS (*(volatile unsigned long *)(GPIO_M_BASE + 0x404))
// SNIP other interrupts

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

// Bit Manipulation
#define TOGGLE_BIT(reg, bit) ((reg) ^= (bit))
void toggle_bit(volatile uint32_t *loc, int bit) {
    *loc ^= bit;
}

#define UNSET_BIT(reg, bit)((reg) &= (~bit))
void unset_bit(volatile uint32_t *loc, int bit) {
    *loc &= ~bit;
}

#define SET_BIT(reg, bit)((reg) |= (bit))
void set_bit(volatile uint32_t *loc, int bit) {
    *loc |= bit;
}

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
    // Set RS=1 for data mode (we're sending character data, not a command)
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
    
    // Generate enable pulse to latch upper nibble
    delay_us(1);                     // Setup time
    SET_BIT(GPIO_N_DATA, LCD_E);     // Enable high
    delay_us(1);                     // Enable pulse width
    UNSET_BIT(GPIO_N_DATA, LCD_E);   // Enable low
    delay_us(50);                    // Hold time
    
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
    
    // Generate enable pulse to latch lower nibble
    delay_us(1);                     // Setup time
    SET_BIT(GPIO_N_DATA, LCD_E);     // Enable high
    delay_us(1);                     // Enable pulse width
    UNSET_BIT(GPIO_N_DATA, LCD_E);   // Enable low
    delay_us(50);                    // Hold time
    
    // Character write completion delay
    delay_us(50);
}

int main() {
    delay_ms(20);
    init_screen();
    lcd_put_char('M');
    while(1) {
        delay_ms(1000);
    }

    return 0;
}
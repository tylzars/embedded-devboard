#ifndef global
#define global

// Boolean
#define bool uint8_t
#define false 0
#define true 1

// Bit Manipulation Macros
#define TOGGLE_BIT(reg, bit) ((reg) ^= (bit))
#define UNSET_BIT(reg, bit)  ((reg) &= (~bit))
#define SET_BIT(reg, bit)    ((reg) |= (bit))

// Integers
#define size_t uint32_t

// Types (Thoughts???)
typedef volatile uint32_t* register32_t;
typedef volatile uint16_t* register16_t;

// Common Registers
#define SYSCTL_RCGCGPIO  (*(register32_t)0x400FE608)
#define SYSCTL_GPIOHBCTL (*(register32_t)0x400FE06C)

// Functionality
void delay_ms(int ms);
void delay_us(int us);
void enable_irqs(void);
void disable_irqs(void);

#endif
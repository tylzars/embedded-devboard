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

typedef struct {
    volatile uint32_t isr_en0;
    volatile uint32_t isr_en1;
    volatile uint32_t isr_en2;
    volatile uint32_t isr_en3;
    volatile uint32_t isr_dis0;
    volatile uint32_t isr_dis1;
    volatile uint32_t isr_dis2;
    volatile uint32_t isr_dis3;
} nvic_t;

// Common Registers
#define SYSCTL_RCGCGPIO         (*(register32_t)0x400FE608)
#define SYSCTL_GPIOHBCTL        (*(register32_t)0x400FE06C)

#define CORE_PERIPHERAL_BASE    0xE000E000
#define NVIC_BASE               (CORE_PERIPHERAL_BASE + 0x100) // same as below
#define NVIC                    ((nvic_t*)NVIC_BASE) // this must be wrapped in parens

// Functionality
void delay_ms(int ms);
void delay_us(int us);
void enable_irqs(void);
void disable_irqs(void);

#endif
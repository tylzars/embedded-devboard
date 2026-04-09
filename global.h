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
#define BIT(bit)             (1U << (bit))

// Integers
#define size_t uint32_t

// Types
#define __IM    const volatile      // Peripheral to CPU (RO)
#define __OM    volatile            // CPI to Peripheral (WO)
#define __IOM   volatile            // Bi-directional

typedef struct {
    __IOM uint32_t isr_en0;
    __IOM uint32_t isr_en1;
    __IOM uint32_t isr_en2;
    __IOM uint32_t isr_en3;
    __IM uint8_t reserved0[0x70];
    __IOM uint32_t isr_dis0;
    __IOM uint32_t isr_dis1;
    __IOM uint32_t isr_dis2;
    __IOM uint32_t isr_dis3;
    __IM uint8_t reserved1[0x70];
    __IOM uint32_t isr_pend0;
    __IOM uint32_t isr_pend1;
    __IOM uint32_t isr_pend2;
    __IOM uint32_t isr_pend3;
    __IM uint8_t reserved2[0x70];
    __IOM uint32_t isr_unpend0;
    __IOM uint32_t isr_unpend1;
    __IOM uint32_t isr_unpend2;
    __IOM uint32_t isr_unpend3;
    __IM uint8_t reserved3[0x70];
    __IM uint32_t isr_active0;    // RO 
    __IM uint32_t isr_active1;    // RO
    __IM uint32_t isr_active2;    // RO
    __IM uint32_t isr_active3;    // RO
    // Priority... TODO
} nvic_t;

// Common Registers
#define SYSCTL_RCGCGPIO         (*(volatile uint32_t*)0x400FE608)
#define SYSCTL_GPIOHBCTL        (*(volatile uint32_t*)0x400FE06C)

#define CORE_PERIPHERAL_BASE    0xE000E000
#define NVIC                    ((nvic_t*)(CORE_PERIPHERAL_BASE + 0x100))

#define TIMER0_ISR BIT(19)

// Functionality
void delay_ms(int ms);
void delay_us(int us);
void enable_irqs(void);
void disable_irqs(void);

#endif
#include "timer.h"

#define DEFAULT Default_Handler

// Stack top (end of RAM)
extern unsigned long _estack;

// Function prototypes
void Reset_Handler(void);
void Default_Handler(void);
void bus_fault_handler(void);
void memory_management_fault_handler(void);

// Weak aliases for exception handlers
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));

void HardFault_Handler(void) {
    extern void seven_seg_show_hex(int);
    seven_seg_show_hex(0xFB);
    while(1);
}

// Vector table
__attribute__((section(".isr_vector")))
void (*const vector_table[])(void) = {
    (void (*)(void))&_estack,       // Initial stack pointer
    Reset_Handler,                  // Reset handler
    NMI_Handler,                    // NMI handler
    HardFault_Handler,              // Hard fault handler
    memory_management_fault_handler,// 4  - Memory management fault
    bus_fault_handler,              // 5  - Bus fault
    DEFAULT,                        // 6  - Usage fault
    0, 0, 0, 0,                     // 7-10 - Reserved
    DEFAULT,                        // 11 - SVCall
    DEFAULT,                        // 12 - Reserved for Debug
    0,                              // 13 - Reserved
    DEFAULT,                        // 14 - PendSV
    DEFAULT,                        // 15 - SysTick
    // IRQs
    DEFAULT, DEFAULT, DEFAULT, DEFAULT,  // 16-19
    DEFAULT, DEFAULT, DEFAULT, DEFAULT,  // 20-23
    DEFAULT, DEFAULT, DEFAULT, DEFAULT,  // 24-27
    DEFAULT, DEFAULT, DEFAULT, DEFAULT,  // 28-31
    DEFAULT, DEFAULT, DEFAULT, isr_timer0,    // 32-35
    DEFAULT, DEFAULT, DEFAULT, DEFAULT,  // 36-39
    DEFAULT, DEFAULT, DEFAULT, DEFAULT,  // 40-43
    DEFAULT, DEFAULT, DEFAULT, DEFAULT,  // 44-47
    // Add more handlers as needed...
};

// Reset handler - called on startup
void Reset_Handler(void) {    
    // Call main
    extern int main(void);
    main();
    
    // If main returns, loop forever
    while(1);
}

// Default handler for unhandled interrupts
void Default_Handler(void) {
    extern void seven_seg_show_hex(int);
    seven_seg_show_hex(0xFF);
    while(1);
}

void bus_fault_handler(void) {
    extern void seven_seg_show_hex(int);
    seven_seg_show_hex(0xFE);
    while(1);
}

void memory_management_fault_handler(void) {
    extern void seven_seg_show_hex(int);
    seven_seg_show_hex(0xFD);
    while(1);
}

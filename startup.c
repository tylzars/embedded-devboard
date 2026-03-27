#define DEFAULT Default_Handler

#define TIMER timer_iterrupt

// Stack top (end of RAM)
extern unsigned long _estack;

// Function prototypes
void Reset_Handler(void);
void Default_Handler(void);

void timer_iterrupt(void);

// Weak aliases for exception handlers
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));

// Vector table
__attribute__((section(".isr_vector")))
void (*const vector_table[])(void) = {
    (void (*)(void))&_estack,       // Initial stack pointer
    Reset_Handler,                  // Reset handler
    NMI_Handler,                    // NMI handler
    HardFault_Handler,              // Hard fault handler
    DEFAULT,                        // 4  - Memory management fault
    DEFAULT,                        // 5  - Bus fault
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
    DEFAULT, DEFAULT, DEFAULT, TIMER,    // 32-35
    DEFAULT, DEFAULT, DEFAULT, DEFAULT,  // 36-39
    DEFAULT, DEFAULT, DEFAULT, DEFAULT,  // 40-43
    DEFAULT, DEFAULT, DEFAULT, DEFAULT,  // 44-47
    // Add more handlers as needed...
};

// Reset handler - called on startup
void Reset_Handler(void) {
    // Initialize variables if needed (we're keeping it simple)
    
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

// TODO: this always triggers on first boot
void timer_iterrupt(void) {
    *(volatile long*)(0x40030000 + 0x024) = 1 << 0; // unfreeze the os
    extern void seven_seg_show_hex(int);
    seven_seg_show_hex(0x11);
    return;
}
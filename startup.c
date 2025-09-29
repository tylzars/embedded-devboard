// Stack top (end of RAM)
extern unsigned long _estack;

// Function prototypes
void Reset_Handler(void);
void Default_Handler(void);

// Weak aliases for exception handlers
void NMI_Handler(void) __attribute__((weak, alias("Default_Handler")));
void HardFault_Handler(void) __attribute__((weak, alias("Default_Handler")));

// Vector table
__attribute__((section(".isr_vector")))
void (*const vector_table[])(void) = {
    (void (*)(void))&_estack,     // Initial stack pointer
    Reset_Handler,                // Reset handler
    NMI_Handler,                  // NMI handler
    HardFault_Handler,            // Hard fault handler
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
    while(1);
}
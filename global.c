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

void disable_irqs(void) {
    asm volatile ("cpsid i");
}

void enable_irqs(void) {
    asm volatile ("cpsie i");
}
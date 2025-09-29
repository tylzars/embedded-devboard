/* Memory layout for TM4C1294NCPDT */
MEMORY
{
    FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 1024K
    SRAM (rwx) : ORIGIN = 0x20000000, LENGTH = 256K
}

/* Stack pointer at end of RAM */
_estack = ORIGIN(SRAM) + LENGTH(SRAM);

SECTIONS
{
    /* Vector table goes first in flash */
    .isr_vector :
    {
        KEEP(*(.isr_vector))
    } > FLASH

    /* Program code */
    .text :
    {
        *(.text*)
        *(.rodata*)
    } > FLASH

    /* Initialized data (copied from flash to RAM at startup) */
    .data :
    {
        _sdata = .;
        *(.data*)
        _edata = .;
    } > SRAM AT > FLASH

    /* Uninitialized data (zeroed at startup) */
    .bss :
    {
        _sbss = .;
        *(.bss*)
        *(COMMON)
        _ebss = .;
    } > SRAM
}
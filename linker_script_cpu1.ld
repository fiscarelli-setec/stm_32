MEMORY
{
    FLASH (rx) : ORIGIN = 0x08000000, LENGTH = 1024K
    RAM_D1 (xrw) : ORIGIN = 0x24000000, LENGTH = 512K
}

SECTIONS
{
    /* Code and read-only data in FLASH */
    .text : {
        KEEP(*(.isr_vector)) /* Interrupt vector table */
        *(.text*)           /* Code */
        *(.rodata*)         /* Read-only data */
        . = ALIGN(4);       /* Ensure 4-byte alignment */
    } > FLASH

    /* Initialized data in RAM_D1 */
    .data : {
        _sdata = .;         /* Start of .data section */
        *(.data*)           /* Initialized data */
        . = ALIGN(4);       /* Ensure 4-byte alignment */
        _edata = .;         /* End of .data section */
    } > RAM_D1 AT > FLASH

    /* Uninitialized data (BSS) in RAM_D1 */
    .bss : {
        _sbss = .;          /* Start of .bss section */
        *(.bss*)            /* Uninitialized data */
        *(COMMON)           /* Common blocks */
        . = ALIGN(4);       /* Ensure 4-byte alignment */
        _ebss = .;          /* End of .bss section */
    } > RAM_D1

    /* Heap definition */
    .heap (NOLOAD) : {
        _heap_start = .;    /* Start of heap */
        . += 0x8000;        /* 32KB heap */
        _heap_end = .;      /* End of heap */
    } > RAM_D1

    /* Stack definition */
    .stack (NOLOAD) : {
        _stack_start = .;   /* Start of stack */
        . += 0x8000;        /* 32KB stack */
        _stack_end = .;     /* End of stack */
    } > RAM_D1

    /* Symbols for system calls and debugging */
    _end = _heap_end;       /* End of memory */
    PROVIDE(__bss_start__ = _sbss); /* Provide _bss_start__ */
    PROVIDE(__bss_end__ = _ebss);   /* Provide _bss_end__ */
}

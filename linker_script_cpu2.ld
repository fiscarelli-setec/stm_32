MEMORY
{
    FLASH (rx) : ORIGIN = 0x08100000, LENGTH = 1024K  /* Flash separata per CM4 */
    RAM_D2 (xrw) : ORIGIN = 0x30000000, LENGTH = 288K /* RAM dedicata a CM4 */
}

SECTIONS
{
    /* Sezione codice e dati read-only nella FLASH */
    .text : {
        KEEP(*(.isr_vector)) /* Tabella vettori interruzioni */
        *(.text*)           /* Codice */
        *(.rodata*)         /* Dati read-only */
        . = ALIGN(4);       /* Allineamento a 4 byte */
    } > FLASH

    /* Dati inizializzati in RAM_D2 */
    .data : {
        _sdata = .;         /* Inizio sezione .data */
        *(.data*)           /* Dati inizializzati */
        . = ALIGN(4);       /* Allineamento a 4 byte */
        _edata = .;         /* Fine sezione .data */
    } > RAM_D2 AT > FLASH

    /* Dati non inizializzati (BSS) in RAM_D2 */
    .bss : {
        _sbss = .;          /* Inizio sezione .bss */
        *(.bss*)            /* Dati non inizializzati */
        *(COMMON)           /* Blocchi comuni */
        . = ALIGN(4);       /* Allineamento a 4 byte */
        _ebss = .;          /* Fine sezione .bss */
    } > RAM_D2

    /* Heap */
    .heap (NOLOAD) : {
        _heap_start = .;    /* Inizio heap */
        . += 0x8000;        /* 32KB heap */
        _heap_end = .;      /* Fine heap */
    } > RAM_D2

    /* Stack */
    .stack (NOLOAD) : {
        _stack_start = .;   /* Inizio stack */
        . += 0x8000;        /* 32KB stack */
        _stack_end = .;     /* Fine stack */
    } > RAM_D2

    /* Simboli per system call */
    _end = _heap_end;       /* Fine memoria */
    PROVIDE(__bss_start__ = _sbss); /* Definizione __bss_start__ */
    PROVIDE(__bss_end__ = _ebss);   /* Definizione __bss_end__ */
}

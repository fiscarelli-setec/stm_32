    .section .text.Reset_Handler
    .global Reset_Handler

Reset_Handler:
    ldr sp, =_estack
    bl main

/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
 
.section ".text.boot"

.global _start

_start:
    /* Stop all non-essential cores */
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, switch_EL
    
switch_EL:
	/* Stack before code */
    ldr     x1, =_start
    mrs     x0, CurrentEL
    and     x0, x0, #12
    
config_EL1:  
	cmp     x0, #4
    beq     clear_bss
    msr     sp_el1, x1

    /* Enable CNTP for EL1 */
    mrs     x0, cnthctl_el2
    orr     x0, x0, #3
    msr     cnthctl_el2, x0
    msr     cntvoff_el2, xzr

    /* Enable AArch64 in EL1 */
    mov     x0, #(1 << 31)     
    orr     x0, x0, #(1 << 1)
    msr     hcr_el2, x0
    mrs     x0, hcr_el2
    
    /* Exception vectors */
    ldr     x2, =_exception_vectors
    msr     vbar_el1, x2
    
	/* Change to EL1 */
    mov     x2, #0x3c4
    msr     spsr_el2, x2
    adr     x2, clear_bss
    msr     elr_el2, x2
    eret

	/* Clear bss */
clear_bss:  mov     sp, x1
    ldr     x1, =__bss_start
    ldr     w2, =__bss_size

loop:  
	cbz     w2, load_C
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, loop

    /* Jump to kernel_main() and stop core0 */
load_C:  
	bl      kernel_main
    b       stop_core

stop_core:  wfe
    b       stop_core


    .align 11
_exception_vectors:

    /* Synchronous */
    .align  7
    mov     x0, #0
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exception_handler

    /* IRQ          */
    .align  7
    mov     x0, #1
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exception_handler

    /* FIQ          */
    .align  7
    mov     x0, #2
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exception_handler

    /* System Error */
    .align  7
    mov     x0, #3
    mrs     x1, esr_el1
    mrs     x2, elr_el1
    mrs     x3, spsr_el1
    mrs     x4, far_el1
    b       exception_handler

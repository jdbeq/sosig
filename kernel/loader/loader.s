/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

.section ".text.boot"

.global _start

_start:
/* identify cpu and idle extra cores */
    mrs     x1, mpidr_el1
    and     x1, x1, #3
    cbz     x1, 2f

/* if not 0 stop */
1:  wfe
    b       1b

/* If cpu id == 0 setup stack */
2:  ldr     x1, =_start
    mov     sp, x1
    ldr     x1, =__bss_start
    ldr     w2, =__bss_size

3:  cbz     w2, 4f
    str     xzr, [x1], #8
    sub     w2, w2, #1
    cbnz    w2, 3b

/* call kernel_main() */
4:  bl      kernel_main
    b       1b

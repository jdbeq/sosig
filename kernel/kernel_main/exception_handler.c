/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "uart1.h"
#include <stdio.h>

void dump_registers(unsigned long esr, unsigned long elr, unsigned long spsr, unsigned long far)
{   
    /* Dump the Registers */
    printf(":\n  ESR_EL1 ");
    uart1_send_hex(esr>>32);
    uart1_send_hex(esr);
    printf(" ELR_EL1 ");
    uart1_send_hex(elr>>32);
    uart1_send_hex(elr);
    printf("\n SPSR_EL1 ");
    uart1_send_hex(spsr>>32);
    uart1_send_hex(spsr);
    printf(" FAR_EL1 ");
    uart1_send_hex(far>>32);
    uart1_send_hex(far);
    printf("\n");
}

/* Universal exception handler */
void exception_handler(unsigned long type, unsigned long esr, unsigned long elr, unsigned long spsr, unsigned long far)
{
    /* Interruption type */
    switch(type) 
    {
        case -0: printf("Synchronous"); break;
        case 1: printf("IRQ"); break;
        case 2: printf("FIQ"); break;
        case 3: printf("SError"); break;
    }
    printf(": ");
    
    /* Decode exception type */
    /* TODO: FINISH FILLING OUT TYPES */
    switch(esr>>26)
    {
        case 0b000000: printf("Unknown"); break;
        case 0b000001: printf("Trapped WFI/WFE"); break;
        case 0b001110: printf("Illegal execution"); break;
        case 0b010101: printf("System call"); break;
        case 0b100000: printf("Instruction abort, lower EL"); break;
        case 0b100001: printf("Instruction abort, same EL"); break;
        case 0b100010: printf("Instruction alignment fault"); break;
        case 0b100100: printf("Data abort, lower EL"); break;
        case 0b100101: printf("Data abort, same EL"); break;
        case 0b100110: printf("Stack alignment fault"); break;
        case 0b101100: printf("Floating point"); break;
        default: printf("Unknown"); break;
    }
    
    /* decode data abort cause */
    if(esr>>26==0b100100 || esr>>26==0b100101) 
    {
        printf(", ");
        switch((esr>>2)&0x3) 
        {
            case 0: printf("Address size fault"); break;
            case 1: printf("Translation fault"); break;
            case 2: printf("Access flag fault"); break;
            case 3: printf("Permission fault"); break;
        }
        
        switch(esr&0x3) 
        {
            case 0: printf(" at level 0"); break;
            case 1: printf(" at level 1"); break;
            case 2: printf(" at level 2"); break;
            case 3: printf(" at level 3"); break;
        }
    }
	/* Dump the appropriate registers */
	dump_registers(esr,elr,spsr,far);
    /* TODO: Figure out some sort of HALT/REBOOT/SOMETHING */
    while(1)
    {
    }
	
}

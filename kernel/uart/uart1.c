#include "gpio.h"
#include "uart1.h"
#include "k_print.h"
void uart1_init()
{
    register unsigned int r;

    /* initialize the UART1 */
    *UART1_ENABLE |=1;           /* enable UART1 */
    *UART1_MU_CNTL = 0;
    *UART1_MU_LCR = 3;           /*  2^3  */
    *UART1_MU_MCR = 0;
    *UART1_MU_IER = 0;
    *UART1_MU_IIR = 0xc6;        /* disable interrupts */
    *UART1_MU_BAUD = 270;        /* 115k baud */
    
    /* Map UART1 to GPIO pins */
    r = *GPFSEL1;
    r &=~ ((7<<12) | (7<<15)); /* gpio14, gpio15 */
    r |= (2<<12) | (2<<15);    /* alt5 */
    
    *GPFSEL1 = r;
    *GPPUD = 0;                // enable pins 14 and 15    

	/* Janky delay.  Need to be finished */
    r = 150; 
    while(r--) 
    { 
        asm volatile("nop");         
    }
    
    *GPPUDCLK0 = (1<<14) | (1<<15);
    r=150; 
    while(r--) 
    { 
        asm volatile("nop");        
    }
    
    /* flush the GPIO setup */
    /* enable transmit and recieve */
    *GPPUDCLK0 = 0;             
    *UART1_MU_CNTL = 3;
    
     k_print("Uart1 Initialized\n");
}

/*   send a character  */
void uart1_send(unsigned int c) {
    /* wait until we can send */
    do{asm volatile("nop");}while(!(*UART1_MU_LSR&0x20));
    /* write the character to the buffer */
    *UART1_MU_IO=c;
}

/* Receive a character */
char uart1_getc() {
    char r;
    /* wait until something is in the buffer */
    do{asm volatile("nop");}while(!(*UART1_MU_LSR&0x01));
    /* read it and return */
    r=(char)(*UART1_MU_IO);
    /* CR to CR+LF */
    return r=='\r'?'\n':r;
}

/* Send a string */

void uart1_puts(char *s) {
    while(*s) {
        /* LF to CR+LF */
        if(*s=='\n')
            uart1_send('\r');
        uart1_send(*s++);
    }
}

void uart1_send_hex(unsigned int d) {
    unsigned int n;
    int c;
    for(c=28;c>=0;c-=4) {
        n=(d >> c) & 0xF;
        n+=n>9?0x37:0x30;
        uart1_send(n);
    }
}

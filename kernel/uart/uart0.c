#include "uart0.h"
#include "mailbox.h"


void uart0_init()
{
    register unsigned int r;

    /* initialize UART0 */
    *UART0_CR = 0;         /* turn off UART0 */

    /* set up clock   */
    /* set clock rate 4mhz */
    mailbox[0] = 9*4;
    mailbox[1] = MAILBOX_REQUEST;
    mailbox[2] = MAILBOX_TAG_SETCLKRATE; 
    mailbox[3] = 12;
    mailbox[4] = 8;
    mailbox[5] = 2;           
    mailbox[6] = 4000000;     
    mailbox[7] = 0;         
    mailbox[8] = MAILBOX_TAG_LAST;
    mailbox_call(MAILBOX_CH_PROP);

    /* map UART0 to GPIO pins */
    r=*GPFSEL1;
    r &=~((7<<12)|(7<<15));
    r|=(4<<12)|(4<<15);    
    *GPFSEL1 = r;
    *GPPUD = 0;            
    r=150; while(r--) { asm volatile("nop"); }
    *GPPUDCLK0 = (1<<14)|(1<<15);
    r=150; while(r--) { asm volatile("nop"); }
    *GPPUDCLK0 = 0;        

    *UART0_ICR = 0x7FF;    
    *UART0_IBRD = 2;       
    *UART0_FBRD = 0xB;
    *UART0_LCRH = 0b11<<5; 
	/* Enable transmit and receive, FIFO */
    *UART0_CR = 0x301;     
}

void uart0_send(unsigned int c) {
    /* wait until we can send */
    do{asm volatile("nop");}while(*UART0_FR&0x20);
    /* write the character to the buffer */
    *UART0_DR=c;
}

/* Hex to binary */
void uart0_send_hex(unsigned int d) {
    unsigned int n;
    int c;
    for(c=28;c>=0;c-=4) {
        n=(d>>c)&0xF;
        n+=n>9?0x37:0x30;
        uart0_send(n);
    }
}

/* Receive a char */
char uart0_getc() {
    char r;
    /* wait until something is in the buffer */
    do{asm volatile("nop");}while(*UART0_FR&0x10);
    /* read and return */

    /* CR = CR+LF */
    return r=='\r'?'\n':r;
}

/* Display a string */
void uart0_puts(char *s) {
    while(*s) {
        if(*s=='\n')
            uart0_send('\r');
        uart0_send(*s++);
    }
}


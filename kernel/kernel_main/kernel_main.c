#include "uart1.h"
#include "mailbox.h"
#include "k_print.h"
#include "uart0.h"


void kernel_main()
{


    k_print("Initializing UART1...\n");
    uart1_init();
    uart1_puts("UART0 Initialized.\n\n");
    
    k_print("Initializing UART0...\n");
    uart0_init();
    uart0_puts("UART0 Initialized.\n");
    
    // Get total amount of RAM and beginning offset
    mailbox[0] = 8*4;                     // Length. TODO: Need standard sizes
    mailbox[1] = MAILBOX_REQUEST;    
    mailbox[2] = MAILBOX_TAG_RAM;
    mailbox[3] = 8;                       // buffer size u32 + u32
    mailbox[4] = 8;
    mailbox[5] = 0;                       // clear output buffer
    mailbox[6] = 0;
    mailbox[7] = MAILBOX_TAG_LAST;

    // send the message to the GPU and receive answer
    if (mailbox_call(MAILBOX_CH_PROP)) 
    {
        k_print("Memory: 0x");
        uart1_send_hex(mailbox[6]);
        k_print("\n");
        k_print("Beginning Offset: 0x");
        uart1_send_hex(mailbox[5]);
        k_print("\n");        

    } else {
        k_print("Error communicating with serial!\n");
    }
    
/*   
    while(1) 
    {
        uart_send_hex(uart_getc());
    }
*/
}

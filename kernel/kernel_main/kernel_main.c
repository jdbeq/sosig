#include "uart.h"
#include "mbox.h"

void kernel_main()
{
    /* Initialize serial console.*/
    uart_init();
    uart_puts("Hello, world!");

    while(1) 
    {
        uart_send(uart_getc());
    }
    
}

#include "uart1.h"
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
        
/*   
    while(1) 
    {
        uart_send_hex(uart_getc());
    }
*/
}

/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
 
#include "uart1.h"
#include "gpio.h"
#include "system.h"
#include "mbox.h"

static uart* uart1 = (uart*)UART_BASE;

void uart1_init(int baud, int bits)
{
    uart1->ENABLES = UART_ENA_MINIUART;

    uart1->MU_IER = 0;

    /* Enable transmitter */
    uart1->MU_CNTL = 0;

    if(bits == 8)
        uart1->MU_LCR = UART_MULCR_8BIT_MODE;
    else
        uart1->MU_LCR = 0;

    uart1->MU_MCR = 0;

    /* Disable all interrupts from MU and clear the fifos */
    uart1->MU_IER = 0;

    uart1->MU_IIR = 0xC6;

    uart1->MU_BAUD = (SYSFREQ / (8 * baud)) - 1;

    /* Setup GPIO 14 and 15 a alt function 5 for UART 1 TX/RX */
    set_gpio_function(GPIO14, FS_ALT5);
    set_gpio_function(GPIO15, FS_ALT5);

    get_gpio()->GPPUD = 0;
    for(volatile int i=0; i<150; i++) { }
    get_gpio()->GPPUDCLK0 = (1 << 14);
    for(volatile int i=0; i<150; i++) { }
    get_gpio()->GPPUDCLK0 = 0;

    /* Enable transmitter and receiver */
    uart1->MU_CNTL = UART_MUCNTL_TX_ENABLE;
}


void uart1_write(char c)
{
    /* Wait until the UART has an empty space in the FIFO */
    while((uart1->MU_LSR & UART_MULSR_TX_EMPTY) == 0) { }

    /* Write the character to the FIFO for transmission */
    uart1->MU_IO = c;
}

uart* get_uart(void)
{
    return uart1;
}

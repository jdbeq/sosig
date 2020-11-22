#include "uart.h"

void k_print(char *s)
{
    uart_puts(s);
}

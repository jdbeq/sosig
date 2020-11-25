#include "uart1.h"

void k_print(char *s)
{
    uart1_puts(s);
}

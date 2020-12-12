#include "stdio.h"
#include "uart1.h"

void printf(char *s)
{
    uart1_puts(s);
}

#include "uart1.h"
#include "uart0.h"
#include "stdio.h"
#include "stdbool.h"
void kernel_main()
{	
        bool x = true;
	if (x)
	{
	    printf("Hello SOSig\n");
	}
	uart0_init();
	uart1_init();
          
}

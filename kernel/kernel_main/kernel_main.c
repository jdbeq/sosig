#include "uart1.h"
#include "uart0.h"

void kernel_main()
{	
	uart0_init();
	uart1_init();
          
}

/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "uart1.h"
#include "uart0.h"
//#include "stdio.h"
#include "stdbool.h"
#include <stdio.h>
void kernel_main()
{	
        bool x = true;
	if (x)
	{
	   // printf("Hello SOSig\n");
	}
	uart0_init();
	uart1_init();

}

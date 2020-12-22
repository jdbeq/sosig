/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
 
#include "uart0.h"
#include "stdio.h"

void kernel_main(void)
{	
	unsigned int test;
    int z = 31337;
	
	printf("Hello, SOSiG!\n");

	printf("Testing printf with hex: %x\n", z );
	printf("Testing printf with d: %d\n", z );
		
	test=*((volatile unsigned int*)0xFFFFFFFFFF000000);
}

/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "delay.h"

void wait_cycles(unsigned int cycles)
{
    if (cycles > 0) 
    {
		while(cycles) 
		{ 
			asm volatile("nop");
			cycles--; 
		}
	}
}

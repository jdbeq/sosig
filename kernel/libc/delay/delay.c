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

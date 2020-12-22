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

void wait_msec(unsigned int msec)
{
    register unsigned long  current_freq;
    register unsigned long  current_count;
    register unsigned long  expire;
    
    asm volatile ("mrs %0, cntfrq_el0" : "=r"(current_freq));
    asm volatile ("mrs %0, cntpct_el0" : "=r"(current_count));
    
    current_count+=((current_freq/1000)* msec)/1000;
    
    do{asm volatile ("mrs %0, cntpct_el0" : "=r"(expire));} while(expire<current_count);
}

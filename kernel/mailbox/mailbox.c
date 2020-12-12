/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "mailbox.h"
#include "gpio.h"

#define MAILBOX_RESPONSE   0x80000000
#define MAILBOX_EMPTY      0x40000000
#define MAILBOX_FULL       0x80000000

#define GPU_MAILBOX        (MMIO_BASE+0x0000B880)
#define MAILBOX_READ       ((volatile unsigned int*)(GPU_MAILBOX+0x0))
#define MAILBOX_POLL       ((volatile unsigned int*)(GPU_MAILBOX+0x10))
#define MAILBOX_SENDER     ((volatile unsigned int*)(GPU_MAILBOX+0x14))
#define MAILBOX_STATUS     ((volatile unsigned int*)(GPU_MAILBOX+0x18))
#define MAILBOX_CONFIG     ((volatile unsigned int*)(GPU_MAILBOX+0x1C))
#define MAILBOX_WRITE      ((volatile unsigned int*)(GPU_MAILBOX+0x20))


/* Must be aligned */
volatile unsigned int  __attribute__((aligned(16))) mailbox[36];

/* 0 on failure, non-zero on success */
int mailbox_call(unsigned char ch)
{
    unsigned int c = (((unsigned int)((unsigned long)&mailbox)&~0xF) | (ch&0xF));

    do {
        asm volatile("nop");
        
    } while(*MAILBOX_STATUS & MAILBOX_FULL);
        
    *MAILBOX_WRITE = c;

    /* Wait for response */
    while(1)
    {
        /* Check response to see for our msg */
        do 
        {
            asm volatile("nop");
            
        } while(*MAILBOX_STATUS & MAILBOX_EMPTY);
        
        if(c == *MAILBOX_READ)
        {
            return mailbox[1]==MAILBOX_RESPONSE;
        }
    }
    return 0;
}

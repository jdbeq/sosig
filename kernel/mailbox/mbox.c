/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
 
#include <stdint.h>

#include "gpio.h"
#include "mbox.h"
#include "mbox_properties.h"

/* Mailbox 0 mapped to base address */
static mbox* mbox0 = (mbox*)MAILBOX0_BASE;

void mbox0_write(mbox0_channel channel, int value)
{
    /* Channel number in lower 4 bits */
    value &= ~(0xF);
    value |= channel;

    /* Wait until the mbox becomes available and then write to the mbox
       channel */
    while((mbox0->Status & MB_STATUS_FULL) != 0) { }
    mbox0->Write = value;
}


int mbox0_read(mbox0_channel channel)
{
    int value = -1;
    /* Keep reading the register until the proper channel returns. */
    while((value & 0xF) != channel)
    {
		while(mbox0->Status & MB_STATUS_EMPTY) { }
        value = mbox0->READ_MBOX;
    }

    /* Return upper 28-bits where value is stored. */
    return value >> 4;
}

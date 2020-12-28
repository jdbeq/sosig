#ifndef MBOX_H
#define MBOX_H

#include "gpio.h"

/* Mailbox Channels */
typedef enum
{
    MBOX0_POWER_MANAGEMENT = 0,
    MBOX0_FRAMEBUFFER,
    MBOX0_VIRTUAL_UART,
    MBOX0_VCHIQ,
    MBOX0_BUTTONS,
    MBOX0_TAGS_ARM_TO_VC,
    MBOX0_TAGS_VC_TO_ARM,
} mbox0_channel;


/* Control register access to a mbox. */
typedef struct {
    volatile unsigned int READ_MBOX;
    volatile unsigned int reserved1[((0x90 - 0x80) / 4) - 1];
    volatile unsigned int POLL_MBOX;
    volatile unsigned int SENDER;
    volatile unsigned int STATUS;
    volatile unsigned int CONFIG;
    volatile unsigned int WRITE;
    } mbox;

enum mbox_status_reg_bits 
{
    MB_STATUS_FULL  = 0x80000000,
    MB_STATUS_EMPTY = 0x40000000,
    MB_STATUS_LEVEL = 0x400000FF,
};

extern void mbox0_write(mbox0_channel channel, int value);
extern int mbox0_read(mbox0_channel channel);

#endif

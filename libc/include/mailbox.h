/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

extern volatile unsigned int mailbox[36];

#define MAILBOX_REQUEST    0

#define MAILBOX_CH_PWR   0
#define MAILBOX_CH_FB      1
#define MAILBOX_CH_VUART   2
#define MAILBOX_CH_VCHIQ   3
#define MAILBOX_CH_LEDS    4
#define MAILBOX_CH_BTNS    5
#define MAILBOX_CH_TOUCH   6
#define MAILBOX_CH_COUNT   7
#define MAILBOX_CH_PROP    8

/* Tags */
#define MAILBOX_TAG_RAM      0x00010005
#define MAILBOX_TAG_LAST           0
#define MAILBOX_TAG_GETSERIAL      0x10004
#define MAILBOX_TAG_SETCLKRATE     0x38002
#define MAILBOX_TAG_LAST           0

int mailbox_call(unsigned char ch);

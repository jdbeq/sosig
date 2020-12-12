/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "mailbox.h"
/*
  Predefined mailbox tags
*/

typedef enum
{
    TAG_BOARD_MODEL =   0x00100001,
    TAG_BOARD_SERIAL =  0x00010004,
    TAG_BOARD_REV =     0x00010002,
    TAG_ARM_MEM =       0x00010005,
    TAG_VCORE_MEM =     0x00010006,
    TAG_VID_FIRMWARE_VERSION = 0x1000000
    
} mailbox_tags;

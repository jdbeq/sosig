#include "stdint.h"
#include "stddef.h"
#include "stdarg.h"
#include <stdio.h>
#include "string.h"

#include "mbox.h"
#include "mbox_properties.h"

static int property_tag[8192] __attribute__((aligned(16)));
static int tag_index = 0;

void property_init(void)
{
    /* Fill in the size on-the-fly */
    property_tag[PT_OSIZE] = 12;

    /* Process request (All other values are reserved!) */
    property_tag[PT_OREQUEST_OR_RESPONSE] = 0;

    /* First available data slot */
    tag_index = 2;

    /* NULL tag to terminate tag list */
    property_tag[tag_index] = 0;
}

void property_add_tag(mb_tag tag, ...)
{
    va_list vl;
    va_start(vl, tag);

    property_tag[tag_index++] = tag;

 switch(tag)
    {
        case TAG_GET_FIRMWARE_VERSION:
			property_tag[tag_index++] = 8;
			property_tag[tag_index++] = 0;
			tag_index +=2;
			break;
			
        case TAG_GET_BOARD_MODEL:
        case TAG_GET_BOARD_REVISION:
        case TAG_GET_BOARD_MAC_ADDRESS:
        case TAG_GET_BOARD_SERIAL:
        case TAG_GET_ARM_MEMORY:
        case TAG_GET_VC_MEMORY:
        case TAG_GET_DMA_CHANNELS:
            /* Provide an 8-byte buffer for the response */
            property_tag[tag_index++] = 8;
            property_tag[tag_index++] = 0; /* Request */
            tag_index += 2;
            break;

        case TAG_GET_CLOCKS:
        case TAG_GET_COMMAND_LINE:
            property_tag[tag_index++] = 256;
            property_tag[tag_index++] = 0;
            tag_index += 256 >> 2;
            break;

        case TAG_ALLOCATE_BUFFER:
        case TAG_GET_MAX_CLOCK_RATE:
        case TAG_GET_MIN_CLOCK_RATE:
        case TAG_GET_CLOCK_RATE:
            property_tag[tag_index++] = 8;
            property_tag[tag_index++] = 0;
            property_tag[tag_index++] = va_arg(vl, int);
            property_tag[tag_index++] = 0;
            break;

        case TAG_SET_CLOCK_RATE:
            property_tag[tag_index++] = 12;
            property_tag[tag_index++] = 0;
            property_tag[tag_index++] = va_arg(vl, int); /* Clock ID */
            property_tag[tag_index++] = va_arg(vl, int); /* Hz */
            property_tag[tag_index++] = va_arg(vl, int);
            break;

        case TAG_GET_PHYSICAL_SIZE:
        case TAG_SET_PHYSICAL_SIZE:
        case TAG_TEST_PHYSICAL_SIZE:
        case TAG_GET_VIRTUAL_SIZE:
        case TAG_SET_VIRTUAL_SIZE:
        case TAG_TEST_VIRTUAL_SIZE:
        case TAG_GET_VIRTUAL_OFFSET:
        case TAG_SET_VIRTUAL_OFFSET:
            property_tag[tag_index++] = 8;
            property_tag[tag_index++] = 0; 
            if((tag == TAG_SET_PHYSICAL_SIZE) ||
                (tag == TAG_SET_VIRTUAL_SIZE) ||
                (tag == TAG_SET_VIRTUAL_OFFSET) ||
                (tag == TAG_TEST_PHYSICAL_SIZE) ||
                (tag == TAG_TEST_VIRTUAL_SIZE))
            {
                property_tag[tag_index++] = va_arg(vl, int); /* Width */
                property_tag[tag_index++] = va_arg(vl, int); /* Height */
            }
            else
            {
                tag_index += 2;
            }
            break;

        case TAG_GET_ALPHA_MODE:
        case TAG_SET_ALPHA_MODE:
        case TAG_GET_DEPTH:
        case TAG_SET_DEPTH:
        case TAG_GET_PIXEL_ORDER:
        case TAG_SET_PIXEL_ORDER:
        case TAG_GET_PITCH:
            property_tag[tag_index++] = 4;
            property_tag[tag_index++] = 0;
            if((tag == TAG_SET_DEPTH) ||
                (tag == TAG_SET_PIXEL_ORDER) ||
                (tag == TAG_SET_ALPHA_MODE))
            {
                /* Pixel Order State */
                property_tag[tag_index++] = va_arg(vl, int);
            }
            else
            {
                tag_index += 1;
            }
            break;

        case TAG_GET_OVERSCAN:
        case TAG_SET_OVERSCAN:
            property_tag[tag_index++] = 16;
            property_tag[tag_index++] = 0;

            if((tag == TAG_SET_OVERSCAN))
            {
                property_tag[tag_index++] = va_arg(vl, int); /* Top */
                property_tag[tag_index++] = va_arg(vl, int); /* Bottom */
                property_tag[tag_index++] = va_arg(vl, int); /* Left */
                property_tag[tag_index++] = va_arg(vl, int); /* Right */
            }
            else
            {
                tag_index += 4;
            }
            break;

        default:
            tag_index--;
            break;
    }
    /* 0 terminated to end the list and update the buffer size */
    property_tag[tag_index] = 0;

    va_end(vl);
}

mbox_property_t* get_property(mb_tag tag)
{
    static mbox_property_t property;
    int* tag_buffer = NULL;

    property.tag = tag;

    /* Get the tag from the buffer, starting with the first tag position */
    int index = 2;

    while(index < (property_tag[PT_OSIZE] >> 2))
    {
        if(property_tag[index] == tag)
        {
            tag_buffer = &property_tag[index];
            break;
        }

        /* Try next tag */
        index += (property_tag[index + 1] >> 2) + 3;
    }

    /* Tag cannot be found in the buffer */
    if(tag_buffer == NULL)
		printf("Null Tag!");
        return NULL;

    property.byte_length = tag_buffer[T_ORESPONSE] & 0xFFFF;
    memcpy(property.data.buffer_8, &tag_buffer[T_OVALUE], property.byte_length);

    return &property;
}

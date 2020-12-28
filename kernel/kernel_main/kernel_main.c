/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#include "stdlib.h"
#include "stddef.h"
#include "stdint.h"
#include <stdio.h>
#include "uart1.h"
#include "system.h"
#include "mbox.h"
#include "mbox_properties.h"

void kernel_main(void)
{
	mbox_property_t *prop;
	uint32_t bus_frequency;
	int32_t cpu_frequency= prop->data.buffer_32[1];
	/* Initialize uart1 for I/O */
	uart1_init(115200, 8);

	/* Initialize mailbox tags */
	property_init();
	/* Add appropriate tags */
	property_add_tag(TAG_GET_CLOCK_RATE, TAG_CLOCK_CORE);		
	/* Bus Prephrial clock rate */
	prop = get_property(TAG_GET_CLOCK_RATE);
		
	bus_frequency = prop->data.buffer_32[1];
	printf("AP Bus Freq: %dMHz\r\n", (bus_frequency / 1000000));
	
	property_add_tag(TAG_GET_CLOCK_RATE, TAG_CLOCK_ARM);
	prop = get_property(TAG_GET_CLOCK_RATE);
	cpu_frequency= abs(prop->data.buffer_32[1]);	
	printf("ARM Frequency: %dMHz\r\n", ( cpu_frequency / 1000000));
	
	int failure = *((volatile unsigned int*)0xFFFFFFFFFF000000);
}

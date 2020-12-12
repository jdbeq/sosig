/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "stdio.h"
#include "uart1.h"

void printf(char *s)
{
    uart1_puts(s);
}

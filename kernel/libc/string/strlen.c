/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include <string.h>

unsigned int strlen(const char* str) 
{
	unsigned int len = 0;
	while (str[len])
	{
	    len++;
	}
	return len;
}

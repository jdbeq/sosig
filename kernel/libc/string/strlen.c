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

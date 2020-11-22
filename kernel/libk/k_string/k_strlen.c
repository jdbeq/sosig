#include "k_string.h"

unsigned int k_strlen(const char* str) {
	unsigned int len = 0;
	while (str[len])
		len++;
	return len;
}

#ifndef _STRING_H
#define _STRING_H 1
 
void *memcpy(void* restrict dstptr, const void* restrict srcptr, unsigned int size);
int memcmp(const void* aptr, const void* bptr, unsigned int size);
unsigned int strlen(const char* str);
void* memmove(void* dstptr, const void* srcptr, unsigned int size);

#endif

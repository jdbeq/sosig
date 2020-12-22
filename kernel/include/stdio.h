/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#include <stdarg.h>

#ifndef _STDIO_H
#define _STDIO_H

//void printf(char *fmt, ...)
void kprint(char *s);
unsigned int sprintf(char *dst, char* fmt, ...);
unsigned int vsprintf(char *dst,char* fmt, va_list args);

#endif

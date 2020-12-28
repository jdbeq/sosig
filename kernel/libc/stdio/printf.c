/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
#include "stdio.h"
#include "stdarg.h"
#include "uart1.h"

volatile unsigned char _end;

unsigned int vsprintf(char *dest, char *format, va_list args)
{
    long int arg;
    int len; 
    int sign; 
    int i;
    char *p; 
    char *orig = dest;
    char tmpstr[19];

    if(dest==(void*)0 || format==(void*)0) 
    {
        return 0;
    }

    arg = 0;
    while(*format) 
    {
        if(*format=='%') 
        {
            format++;
            if(*format=='%') 
            {
                goto put;
            }
            
            len=0;
            
            while(*format>='0' && *format<='9') 
            {
                len *= 10;
                len += *format-'0';
                format++;
            }
            
            /* long not supported */
            if(*format=='l') 
            {
                format++;
            }
            
            if(*format=='c') 
            {
                arg = va_arg(args, int);
                *dest++ = (char)arg;
                format++;
                continue;
            } else
            
            
            if(*format=='d') 
            {
                arg = va_arg(args, int);
                sign=0;
                if((int)arg<0) {
                    arg*=-1;
                    sign++;
                }
                if(arg>99999999999999999L) 
                {
                    arg=99999999999999999L;
                }

                i=18;
                tmpstr[i]=0;
                do 
                {
                    tmpstr[--i]='0'+(arg%10);
                    arg/=10;
                } while(arg!=0 && i>0);
                
                if(sign) 
                {
                    tmpstr[--i]='-';
                }
                
                if(len>0 && len<18) 
                {
                    while(i>18-len) 
                    {
                        tmpstr[--i]=' ';
                    }
                }
                p=&tmpstr[i];
                goto copystring;
            } else
            
            if(*format=='x') 
            {
                arg = va_arg(args, long int);
                i=16;
                tmpstr[i]=0;
                do 
                {
                    char n=arg & 0xf;
                    tmpstr[--i]=n+(n>9?0x37:0x30);
                    arg>>=4;
                } while(arg!=0 && i>0);
                
                if(len>0 && len<=16) 
                {
                    while(i>16-len) {
                        tmpstr[--i]='0';
                    }
                }
                p=&tmpstr[i];
                goto copystring;
            } else
            
            if(*format=='s') 
            {
                p = va_arg(args, char*);

copystring:		if(p==(void*)0) {
					printf("NULL STRING");
                    p="(null)";
                }
                while(*p) {
                    *dest++ = *p++;
                }
            }
        } else {
put:        *dest++ = *format;
        }
        format++;
    }
    *dest=0;
    return dest-orig;
}

/* Variable length arguments */
unsigned int sprintf(char *dst, char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    return vsprintf(dst,fmt,args);
}

void printf(char *fmt, ...) 
{
	va_list args;
    va_start(args, fmt);
	/* TODO: Need to implement memory allocation */
	/* For now, just tag it on the end */
    char *s = (char*)&_end;
    /* Use vsprintf to format our string */
    vsprintf(s,fmt,args);
    while(*s) {
        /* Convert newline to carrige return + newline */
        if(*s=='\n')
            uart1_write('\r');
        uart1_write(*s++);
    }
}


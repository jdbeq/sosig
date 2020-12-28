/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
 
#ifndef GPIO_H
#define GPIO_H

#include "system.h"

#define FS_MASK     (7)

typedef enum {
    IO_LOW = 0,
    IO_HI,
    IO_ON,
    IO_OFF,
    IO_UNKNOWN,
    } gpio_value;

typedef enum {
    FS_INPUT = 0,
    FS_OUTPUT,
    FS_ALT0,
    FS_ALT5,    
    } gpio_alt_function;

typedef enum {
    GPIO0 = 0,GPIO1,GPIO2,GPIO3,GPIO4,GPIO5,GPIO6,GPIO7,GPIO8,GPIO9,
    GPIO10 = 10,GPIO11,GPIO12,GPIO13,GPIO14,GPIO15,GPIO16,GPIO17,GPIO18,
    GPIO19,GPIO20 = 20,GPIO21,GPIO22,GPIO23,GPIO24,GPIO25,GPIO26,GPIO27,
    GPIO28,GPIO29,GPIO30 = 30,GPIO31,GPIO32,GPIO33,GPIO34,GPIO35,GPIO36,
    GPIO37,GPIO38,GPIO39,GPIO40 = 40,GPIO41,GPIO42,GPIO43,GPIO44,GPIO45,
    GPIO46,GPIO47,GPIO48,GPIO49,GPIO50 = 50,GPIO51,GPIO52,GPIO53,
    } gpio_pin;

/*  54 general-purpose I/O */    
typedef struct {
    reg32_rw_t    GPUART_FSEL0;
    reg32_rw_t    GPUART_FSEL1;
    reg32_rw_t    GPUART_FSEL2;
    reg32_rw_t    GPUART_FSEL3;
    reg32_rw_t    GPUART_FSEL4;
    reg32_rw_t    GPUART_FSEL5;
    reg32_ro_t    Reserved0;
    reg32_wo_t    GPSET0;
    reg32_wo_t    GPSET1;
    reg32_ro_t    Reserved1;
    reg32_wo_t    GPCLR0;
    reg32_wo_t    GPCLR1;
    reg32_ro_t    Reserved2;
    reg32_wo_t    GPLEV0;
    reg32_wo_t    GPLEV1;
    reg32_ro_t    Reserved3;
    reg32_wo_t    GPEDS0;
    reg32_wo_t    GPEDS1;
    reg32_ro_t    Reserved4;
    reg32_wo_t    GPREN0;
    reg32_wo_t    GPREN1;
    reg32_ro_t    Reserved5;
    reg32_wo_t    GPFEN0;
    reg32_wo_t    GPFEN1;
    reg32_ro_t    Reserved6;
    reg32_wo_t    GPHEN0;
    reg32_wo_t    GPHEN1;
    reg32_ro_t    Reserved7;
    reg32_wo_t    GPLEN0;
    reg32_wo_t    GPLEN1;
    reg32_ro_t    Reserved8;
    reg32_wo_t    GPAREN0;
    reg32_wo_t    GPAREN1;
    reg32_ro_t    Reserved9;
    reg32_wo_t    GPAFEN0;
    reg32_wo_t    GPAFEN1;
    reg32_ro_t    Reserved10;
    reg32_wo_t    GPPUD;
    reg32_wo_t    GPPUDCLK0;
    reg32_wo_t    GPPUDCLK1;
    reg32_ro_t    Reserved11;
    } gpio_t;

gpio_t* get_gpio(void);
void set_gpio_function(gpio_pin gpio, gpio_alt_function func);
void set_gpio_output(gpio_pin gpio);
void set_gpio_input(gpio_pin gpio);
gpio_value get_gpio_value(gpio_pin gpio);
void set_gpio_hi(gpio_pin gpio);
void set_gpio_low(gpio_pin gpio);
void set_gpio_value(gpio_pin gpio, gpio_value value);
void toggle_gpio(gpio_pin gpio);

#endif

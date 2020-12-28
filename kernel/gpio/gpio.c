/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */

#include "system.h"
#include "stdint.h"
#include "gpio.h"

static gpio_t* gpio0 = (gpio_t*)GPIO_BASE;

gpio_t* get_gpio(void)
{
    return gpio0;
}

void set_gpio_function(gpio_pin gpio, gpio_alt_function func)
{
    reg32_rw_t* fsel_reg = &((reg32_rw_t*)gpio0)[ gpio / 10 ];
    reg32_rw_t fsel_copy = *fsel_reg;
    fsel_copy &= ~(FS_MASK << ((gpio % 10) * 3));
    fsel_copy |= (func << ((gpio % 10) * 3));
    *fsel_reg = fsel_copy;
}

void set_gpio_output(gpio_pin gpio)
{
    set_gpio_function(gpio, FS_OUTPUT);
}

void set_gpio_input(gpio_pin gpio)
{
    set_gpio_function(gpio, FS_INPUT);
}

gpio_value get_gpio_value(gpio_pin gpio)
{
    gpio_value result = IO_UNKNOWN;

    switch(gpio / 32)
    {
        case 0:
            result = gpio0->GPLEV0 & (1 << gpio);
            break;

        case 1:
            result = gpio0->GPLEV1 & (1 << (gpio - 32));
            break;

        default:
            break;
    }

    if(result != IO_UNKNOWN)
    {
        if(result)
            result = IO_HI;
    }

    return result;
}


void toggle_gpio(gpio_pin gpio)
{
    if(get_gpio_value(gpio))
        set_gpio_low(gpio);
    else
        set_gpio_hi(gpio);
}


void set_gpio_hi(gpio_pin gpio)
{
    switch(gpio / 32)
    {
        case 0:
            gpio0->GPSET0 = (1 << gpio);
            break;

        case 1:
            gpio0->GPSET1 = (1 << (gpio - 32));
            break;

        default:
            break;
    }
}


void set_gpio_low(gpio_pin gpio)
{
    switch(gpio / 32)
    {
        case 0:
            gpio0->GPCLR0 = (1 << gpio);
            break;

        case 1:
            gpio0->GPCLR1 = (1 << (gpio - 32));
            break;

        default:
            break;
    }
}


void set_gpio_value(gpio_pin gpio, gpio_value value)
{
    if((value == IO_LOW) || (value == IO_OFF))
        set_gpio_low(gpio);
    else if((value == IO_HI) || (value == IO_ON))
        set_gpio_hi(gpio);
}

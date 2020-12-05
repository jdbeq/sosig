#include "gpio.h"

/* UART1 registers */
#define UART1_ENABLE      ((volatile unsigned int*)(MMIO_BASE+0x00215004))
#define UART1_MU_IO       ((volatile unsigned int*)(MMIO_BASE+0x00215040))
#define UART1_MU_IER      ((volatile unsigned int*)(MMIO_BASE+0x00215044))
#define UART1_MU_IIR      ((volatile unsigned int*)(MMIO_BASE+0x00215048))
#define UART1_MU_LCR      ((volatile unsigned int*)(MMIO_BASE+0x0021504C))
#define UART1_MU_MCR      ((volatile unsigned int*)(MMIO_BASE+0x00215050))
#define UART1_MU_LSR      ((volatile unsigned int*)(MMIO_BASE+0x00215054))
#define UART1_MU_MSR      ((volatile unsigned int*)(MMIO_BASE+0x00215058))
#define UART1_MU_SCRATCH  ((volatile unsigned int*)(MMIO_BASE+0x0021505C))
#define UART1_MU_CNTL     ((volatile unsigned int*)(MMIO_BASE+0x00215060))
#define UART1_MU_STAT     ((volatile unsigned int*)(MMIO_BASE+0x00215064))
#define UART1_MU_BAUD     ((volatile unsigned int*)(MMIO_BASE+0x00215068))


void uart1_init();

void uart1_send(unsigned int c);

char uart1_getc();

void uart1_puts(char *s);

void uart1_send_hex(unsigned int d);

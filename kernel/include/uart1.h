/*
 * This file is subject to the terms and conditions defined in
 * file 'LICENSE.txt', which is part of this source code package.
 */
 
#ifndef UART_H
#define UART_H

#include "gpio.h"


/* Need to determine if it is more economical to hardcode
 * values over shifting bits.
 */
#define UART_BASE    ( MMIO_BASE + 0x215000 )

#define UART_ENA_MINIUART            ( 1 << 0 )
#define UART_ENA_SPI1                ( 1 << 1 )
#define UART_ENA_SPI2                ( 1 << 2 )

#define UART_IRQ_SPI2                ( 1 << 2 )
#define UART_IRQ_SPI1                ( 1 << 1 )
#define UART_IRQ_MU                  ( 1 << 0 )

#define UART_LCR_8BIT_MODE         ( 3 << 0 )
#define UART_LCR_BREAK             ( 1 << 6 )
#define UART_LCR_DLAB_ACCESS       ( 1 << 7 )

#define UART_MCR_RTS               ( 1 << 1 )

#define UART_LSR_DATA_READY        ( 1 << 0 )
#define UART_LSR_RX_OVERRUN        ( 1 << 1 )
#define UART_LSR_TX_EMPTY          ( 1 << 5 )
#define UART_LSR_TX_IDLE           ( 1 << 6 )

#define UART_MSR_CTS               ( 1 << 5 )

#define UART_CNTL_RX_ENABLE        ( 1 << 0 )
#define UART_CNTL_TX_ENABLE        ( 1 << 1 )
#define UART_CNTL_RTS_FLOW         ( 1 << 2 )
#define UART_CNTL_CTS_FLOW         ( 1 << 3 )
#define UART_CNTL_RTS_FIFO         ( 3 << 4 )
#define UART_CNTL_RTS_ASSERT       ( 1 << 6 )
#define UART_CNTL_CTS_ASSERT       ( 1 << 7 )

#define UART_STAT_SYMBOL_AV        ( 1 << 0 )
#define UART_STAT_SPACE_AV         ( 1 << 1 )
#define UART_STAT_RX_IDLE          ( 1 << 2 )
#define UART_STAT_TX_IDLE          ( 1 << 3 )
#define UART_STAT_RX_OVERRUN       ( 1 << 4 )
#define UART_STAT_TX_FIFO_FULL     ( 1 << 5 )
#define UART_STAT_RTS              ( 1 << 6 )
#define UART_STAT_CTS              ( 1 << 7 )
#define UART_STAT_TX_EMPTY         ( 1 << 8 )
#define UART_STAT_TX_DONE          ( 1 << 9 )
#define UART_STAT_RX_FIFO_LEVEL    ( 7 << 16 )
#define UART_STAT_TX_FIFO_LEVEL    ( 7 << 24 )


#define UART_FSEL0(x)        ( x )
#define UART_FSEL1(x)        ( x << 3 )
#define UART_FSEL2(x)        ( x << 6 )
#define UART_FSEL3(x)        ( x << 9 )
#define UART_FSEL4(x)        ( x << 12 )
#define UART_FSEL5(x)        ( x << 15 )
#define UART_FSEL6(x)        ( x << 18 )
#define UART_FSEL7(x)        ( x << 21 )
#define UART_FSEL8(x)        ( x << 24 )
#define UART_FSEL9(x)        ( x << 27 )

#define UART_FSEL10(x)       ( x )
#define UART_FSEL11(x)       ( x << 3 )
#define UART_FSEL12(x)       ( x << 6 )
#define UART_FSEL13(x)       ( x << 9 )
#define UART_FSEL14(x)       ( x << 12 )
#define UART_FSEL15(x)       ( x << 15 )
#define UART_FSEL16(x)       ( x << 18 )
#define UART_FSEL17(x)       ( x << 21 )
#define UART_FSEL18(x)       ( x << 24 )
#define UART_FSEL19(x)       ( x << 27 )

#define UART_FSEL20(x)       ( x )
#define UART_FSEL21(x)       ( x << 3 )
#define UART_FSEL22(x)       ( x << 6 )
#define UART_FSEL23(x)       ( x << 9 )
#define UART_FSEL24(x)       ( x << 12 )
#define UART_FSEL25(x)       ( x << 15 )
#define UART_FSEL26(x)       ( x << 18 )
#define UART_FSEL27(x)       ( x << 21 )
#define UART_FSEL28(x)       ( x << 24 )
#define UART_FSEL29(x)       ( x << 27 )

#define UART_FSEL30(x)       ( x )
#define UART_FSEL31(x)       ( x << 3 )
#define UART_FSEL32(x)       ( x << 6 )
#define UART_FSEL33(x)       ( x << 9 )
#define UART_FSEL34(x)       ( x << 12 )
#define UART_FSEL35(x)       ( x << 15 )
#define UART_FSEL36(x)       ( x << 18 )
#define UART_FSEL37(x)       ( x << 21 )
#define UART_FSEL38(x)       ( x << 24 )
#define UART_FSEL39(x)       ( x << 27 )

#define UART_FSEL40(x)       ( x )
#define UART_FSEL41(x)       ( x << 3 )
#define UART_FSEL42(x)       ( x << 6 )
#define UART_FSEL43(x)       ( x << 9 )
#define UART_FSEL44(x)       ( x << 12 )
#define UART_FSEL45(x)       ( x << 15 )
#define UART_FSEL46(x)       ( x << 18 )
#define UART_FSEL47(x)       ( x << 21 )
#define UART_FSEL48(x)       ( x << 24 )
#define UART_FSEL49(x)       ( x << 27 )

#define UART_FSEL50(x)       ( x )
#define UART_FSEL51(x)       ( x << 3 )
#define UART_FSEL52(x)       ( x << 6 )
#define UART_FSEL53(x)       ( x << 9 )


typedef struct {
    volatile unsigned int IRQ;
    volatile unsigned int ENABLES;

    volatile unsigned int reserved1[((0x40 - 0x04) / 4) - 1];

    volatile unsigned int MU_IO;
    volatile unsigned int MU_IER;
    volatile unsigned int MU_IIR;
    volatile unsigned int MU_LCR;
    volatile unsigned int MU_MCR;
    volatile unsigned int MU_LSR;
    volatile unsigned int MU_MSR;
    volatile unsigned int MU_SCRATCH;
    volatile unsigned int MU_CNTL;
    volatile unsigned int MU_STAT;
    volatile unsigned int MU_BAUD;

    volatile unsigned int reserved2[(0x80 - 0x68) / 4];

    volatile unsigned int SPI0_CNTL0;
    volatile unsigned int SPI0_CNTL1;
    volatile unsigned int SPI0_STAT;
    volatile unsigned int SPI0_IO;
    volatile unsigned int SPI0_PEEK;

    volatile unsigned int reserved3[(0xC0 - 0x94) / 4];

    volatile unsigned int SPI1_CNTL0;
    volatile unsigned int SPI1_CNTL1;
    volatile unsigned int SPI1_STAT;
    volatile unsigned int SPI1_IO;
    volatile unsigned int SPI1_PEEK;
    } uart;

extern uart* get_uart( void );
extern void uart1_init( int baud, int bits );
extern void uart1_write( char c );

#endif

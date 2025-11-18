#pragma once

#include <libs/prelude.h>

#define UART0_IRQ      10
#define UART0_BASE     0x10000000UL

#define UART_COM(base, offset) ((base) + (offset))

#define COM_THR         0 /* In: Transmit Holding Register */
#define COM_RBR         0 /* Out: Receive Buffer Register */
#define COM_DLL         0 /* Out: Divisor Latch Low Byte */
#define COM_DLM         1 /* Out: Divisor Latch High Byte */
#define COM_IER         1 /* Out: Interrupt Enable Register */
    #define COM_IER_RDI     0x01 /* Enable Received Data Interrupt */
#define COM_IIR         2 /* In: Interrupt Identity Register */
#define COM_FCR         2 /* Out: FIFO Control Register */
#define COM_LCR         3 /* Out: Line Control Register */
    #define COM_LCR_DLAB    0x80 /* Divisor Latch Access Bit */
    #define COM_LCR_WLEN8   0x03 /* 8 bits data */
#define COM_MCR         4 /* Out: Modem Control Register */
#define COM_LSR         5 /* In: Line Status Register */
    #define COM_LSR_DR      0x01 /* Data Ready */
    #define COM_LSR_THRE    0x20 /* Transmit-Hold-Register Empty */



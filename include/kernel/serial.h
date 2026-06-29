#ifndef EDOS_SERIAL_H
#define EDOS_SERIAL_H

#include <arch/types.h>

#define COM1 0x3F8

#define UART_RX  0
#define UART_TX  0
#define UART_DLL 0
#define UART_IER 1
#define UART_DLH 1
#define UART_IIR 2
#define UART_FCR 2
#define UART_LCR 3
#define UART_MCR 4
#define UART_LSR 5
#define UART_MSR 6

#define LCR_8BITS    0x03
#define LCR_DLAB     0x80
#define FCR_ENABLE   0x01
#define FCR_CLEAR_RX 0x02
#define FCR_CLEAR_TX 0x03
#define MCR_DTR      0x01
#define MCR_RTS      0x02
#define MCR_OUT2     0x08
#define LSR_DR       0x01
#define LSR_THRE     0x20

#define BAUD_DIV 1

static inline void outb(u16 port, u8 val)
{
	asm volatile ("outb %b0, %w1"
		      :
		      : "a"(val), "Nd"(port)
		      : "memory");
}

static inline u8 inb(u16 port)
{
	u8 ret;

	asm volatile ("inb %w1, %b0"
		      : "=a"(ret)
		      : "Nd"(port)
		      : "memory");
	return ret;
}

void serial_init(void);

void serial_putc(char c);
char serial_getc(void);

#endif

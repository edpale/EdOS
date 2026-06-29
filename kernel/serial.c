#include <kernel/serial.h>

void serial_init(void)
{
	outb(COM1 + UART_IER, 0x00); /* Disable interrupts */

	outb(COM1 + UART_LCR, LCR_DLAB); /* Set DLAB */

	/* Set baud rate */
	outb(COM1 + UART_DLL, BAUD_DIV & 0xFF);
	outb(COM1 + UART_DLH, (BAUD_DIV >> 8) & 0xFF);

	/* Clear DLAB, set line format: 8 bits, 1 stop, no parity */
	outb(COM1 + UART_LCR, LCR_8BITS);

	outb(COM1 + UART_FCR, FCR_ENABLE | FCR_CLEAR_RX | FCR_CLEAR_TX);

	outb(COM1 + UART_MCR, MCR_DTR | MCR_RTS | MCR_OUT2);
}

void serial_putc(char c)
{
	while (!(inb(COM1 + UART_LSR) & LSR_THRE));

	outb(COM1 + UART_TX, c);
}

char serial_getc(void)
{
	while (!(inb(COM1 + UART_LSR) & LSR_DR));

	return inb(COM1 + UART_RX);
}

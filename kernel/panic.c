#include <arch/cpu.h>
#include <kernel/panic.h>
#include <kernel/printf.h>

__noreturn void panic(const char *fmt, ...)
{
	va_list ap;

	kprintf("*** KERNEL PANIC ***\n");

	va_start(ap, fmt);
	kvprintf(fmt, ap);
	va_end(ap);

	kprintf("\n*** PANIC END ***\n");

	for (;;)
		halt();
}

#include <kernel/multiboot2.h>
#include <kernel/printf.h>
#include <kernel/serial.h>

#include "gdt.h"
#include "main.h"

void kmain(u32 magic, paddr_t)
{
	if (magic != MB2_MAGIC)
		return;

	gdt_init();
	serial_init();
	kprintf("Hi from EdOS!\n");
}

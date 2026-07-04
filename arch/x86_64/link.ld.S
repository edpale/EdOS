#include <arch/vmparam.h>

ENTRY(_start)

SECTIONS
{
	. = KERN_START_PHYS;

	.multiboot2 ALIGN(4K) :
	{
		*(.multiboot2)
	}

	.boot ALIGN(4K) :
	{
		*(.boot)
	}

	. += KERN_BASE_VIRT;

	_kernel_start = .;

	.text ALIGN(4K) : AT(ADDR(.text) - KERN_BASE_VIRT)
	{
		*(.text)
	}

	.rodata ALIGN(4K) : AT(ADDR(.rodata) - KERN_BASE_VIRT)
	{
		*(.rodata)
	}

	.data ALIGN(4K) : AT(ADDR(.data) - KERN_BASE_VIRT)
	{
		*(.data)
	}

	.bss ALIGN(4K) : AT(ADDR(.bss) - KERN_BASE_VIRT)
	{
		*(COMMON)
		*(.bss)
	}

	_kernel_end = .;
}

#ifndef EDOS_X86_64_H
#define EDOS_X86_64_H

#include <kernel/bug.h>

#include "vmparam.h"
#include "types.h"

extern char _kernel_start[];
extern char _kernel_end[];

static __always_inline paddr_t kern_va_to_pa(void *va_ptr)
{
	vaddr_t va = (vaddr_t)va_ptr;

	BUG_ON(va < (vaddr_t)_kernel_start);
	return (paddr_t)KERN_TO_PHYS(va);
}

static __always_inline void *kern_pa_to_va(paddr_t pa)
{
	vaddr_t va = (vaddr_t)PHYS_TO_KERN(pa);

	BUG_ON(va < (vaddr_t)_kernel_start);
	return (void *)va;
}

#endif

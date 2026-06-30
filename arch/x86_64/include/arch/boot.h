#ifndef EDOS_X86_64_BOOT_H
#define EDOS_X86_64_BOOT_H

#include "types.h"

/* To be used only while BOOD_IDMAP exists */
static inline void *boot_pa_to_va(paddr_t pa)
{
	return (void *)pa;
}

#endif

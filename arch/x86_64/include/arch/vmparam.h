#ifndef EDOS_X86_64_VMPARAM_H
#define EDOS_X86_64_VMPARAM_H

#include "param.h"

/* Kernel virtual region: the top -2GiB of the 64-bit address space. */
#define KERN_BASE_VIRT UL(0xFFFFFFFF80000000)
#define KERN_REG_SIZE  (-KERN_BASE_VIRT)

#define KERN_START_PHYS PDE_MAP_SIZE

/* Virtual address of the kernel image (base + physical load offset). */
#define KERN_START_VIRT (KERN_BASE_VIRT + KERN_START_PHYS)

/* Convert between kernel virtual region addresses and physical addresses.
 * Valid ONLY for addresses in the kernel virtual region, not for arbitrary
 * physical memory (use the dmap conversions for that). */
#define KERN_TO_PHYS(_va) ((_va) - KERN_BASE_VIRT)
#define PHYS_TO_KERN(_pa) ((_pa) + KERN_BASE_VIRT)

/* Boot identity map: the low 4GiB, mapped virt == phys so early boot
 * code can reach the multiboot information structure and low physical
 * memory before the direct map exists. Torn down once the real
 * page tables and direct map are built. */
#define BOOT_IDMAP_START UL(0x0)
#define	BOOT_IDMAP_END   UL(0x100000000) /* 4GiB */
#define BOOT_IDMAP_SIZE  (BOOT_IDMAP_END - BOOT_IDMAP_START)

#endif

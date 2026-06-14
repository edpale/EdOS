#ifndef EDOS_X86_64_PARAM_H
#define EDOS_X86_64_PARAM_H

#include <kernel/const.h>

#define PAGE_SHIFT 12
#define PAGE_SIZE  (UL(1) << PAGE_SHIFT)
#define PAGE_MASK  (PAGE_SIZE - 1)

#define PTE_SIZE      8
#define NPTE_SHIFT    9
#define NPTE          (UL(1) << NPTE_SHIFT)
#define NPTE_MASK     (NPTE - 1)
#define PT_INDEX(_va) (((_va) >> PAGE_SHIFT) & NPTE_MASK)

#define PDE_SIZE      8
#define NPDE_SHIFT    9
#define NPDE          (UL(1) << NPDE_SHIFT)
#define NPDE_MASK     (NPDE - 1)
#define PDE_MAP_SHIFT (NPTE_SHIFT + PAGE_SHIFT)
#define PDE_MAP_SIZE  (UL(1) << PDE_MAP_SHIFT)
#define PDE_MAP_MASK  (PDE_MAP_SIZE - 1)
#define PD_INDEX(_va) (((_va) >> PDE_MAP_SHIFT) & NPDE_MASK)

#define PDPE_SIZE       8
#define NPDPE_SHIFT     9
#define NPDPE           (UL(1) << NPDPE_SHIFT)
#define NPDPE_MASK      (NPDPE - 1)
#define PDPE_MAP_SHIFT  (NPDPE_SHIFT + PDE_MAP_SHIFT)
#define PDPE_MAP_SIZE   (UL(1) << PDPE_MAP_SHIFT)
#define PDPE_MAP_MASK   (PDPE_MAP_SIZE - 1)
#define PDPT_INDEX(_va) (((_va) >> PDPE_MAP_SHIFT) & NPDPE_MASK)

#define PML4E_SIZE      8
#define NPML4E_SHIFT    9
#define NPML4E          (UL(1) << NPML4E_SHIFT)
#define NPML4E_MASK     (NPML4E - 1)
#define PML4E_MAP_SHIFT (NPML4E_SHIFT + PDPE_MAP_SHIFT)
#define PML4E_MAP_SIZE  (UL(1) << PML4E_MAP_SHIFT)
#define PML4E_MAP_MASK  (PML4E_MAP_SIZE - 1)
#define PML4_INDEX(_va) (((_va) >> PML4E_MAP_SHIFT) & NPML4E_MASK)

#define KERN_STACK_NPAGES 4
#define KERN_STACK_SIZE   (KERN_STACK_NPAGES * PAGE_SIZE)

#endif

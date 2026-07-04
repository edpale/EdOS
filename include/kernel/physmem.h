#ifndef EDOS_PHYSMEM_H
#define EDOS_PHYSMEM_H

#include <arch/types.h>

#include "result.h"

void physmem_init(void);
void physmem_add_region(paddr_t start, paddr_t end);
void physmem_exclude_region(paddr_t start, paddr_t end);
result_t physmem_alloc_pages_in_range(paddr_t range_start, paddr_t range_end,
				      size_t n, paddr_t *out);
#endif

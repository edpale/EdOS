#ifndef EDOS_X86_64_MAIN_H
#define EDOS_X86_64_MAIN_H

#include <arch/types.h>

void kmain(u32 magic, paddr_t mbi_addr);

#endif

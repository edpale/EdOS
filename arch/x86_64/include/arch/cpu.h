#ifndef EDOS_X86_64_CPU_H
#define EDOS_X86_64_CPU_H

static inline void halt(void)
{
	asm volatile ("cli; hlt");
}

#endif

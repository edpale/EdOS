#ifndef EDOS_PANIC_H
#define EDOS_PANIC_H

#include <kernel/cdefs.h>

__noreturn void panic(const char *fmt, ...);

#endif

#ifndef EDOS_BUG_H
#define EDOS_BUG_H

#include "panic.h"
#include "printf.h"
#include "cdefs.h"

#define BUG_ON(_cond)                                      \
	do {                                               \
		if (unlikely(_cond))                       \
			panic("BUG: %s (%s:%d)\n",         \
			      #_cond, __FILE__, __LINE__); \
	} while (0)

#define WARN_ON(_cond)                               \
({                                                   \
	bool __cond = !!(_cond);                     \
	if (unlikely(__cond))                        \
		kprintf("WARNING: %s (%s:%d)\n",     \
			#_cond, __FILE__, __LINE__); \
	__cond;                                      \
})

#endif

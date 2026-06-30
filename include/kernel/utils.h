#ifndef EDOS_UTILS_H
#define EDOS_UTILS_H

#define roundup2(_x, _size)                  \
({                                           \
	typeof(_x) __size = _size;           \
	((_x) + __size - 1) & ~(__size - 1); \
})

#endif

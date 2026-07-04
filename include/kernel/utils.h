#ifndef EDOS_UTILS_H
#define EDOS_UTILS_H

#include "cdefs.h"

#define max(_x, _y)                               \
({                                                \
	typeof(_x) __x = (_x);                    \
	typeof(_y) __y = (_y);                    \
	BUILD_BUG_ON(!TYPE_COMPATIBLE(__x, __y)); \
	__x > __y ? __x : __y;                    \
})

#define min(_x, _y)                               \
({                                                \
	typeof(_x) __x = (_x);                    \
	typeof(_y) __y = (_y);                    \
	BUILD_BUG_ON(!TYPE_COMPATIBLE(__x, __y)); \
	__x < __y ? __x : __y;                    \
})

#define max_as(_type, _x, _y) max((_type)(_x), (_type)(_y))
#define min_as(_type, _x, _y) min((_type)(_x), (_type)(_y))

#define is_pow2(_x)                              \
({                                               \
	typeof(_x) __x = (_x);                   \
	((_x) != 0 && ((_x) & ((_x) - 1)) == 0); \
})

#define rounddown2(_x, _size)        \
({                                   \
	typeof(_x) __size = (_size); \
	(_x) & ~(__size - 1);        \
})

#define roundup2(_x, _size)                  \
({                                           \
	typeof(_x) __size = (_size);         \
	((_x) + __size - 1) & ~(__size - 1); \
})

#define is_aligned(_x, _size)        \
({                                   \
	typeof(_x) __size = (_size); \
	((_x) & (__size - 1)) == 0;  \
})

#endif

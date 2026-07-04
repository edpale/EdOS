#ifndef EDOS_CDEFS_H
#define EDOS_CDEFS_H

#define __aligned(_x)   __attribute__((aligned(_x)))
#define __packed        __attribute__((packed))
#define __noreturn      __attribute__((noreturn))
#define __always_inline inline __attribute__((__always_inline__))
#define __must_check    __attribute__((__warn_unused_result__))

#define likely(x)   __builtin_expect(!!(x), 1)
#define unlikely(x) __builtin_expect(!!(x), 0)

#define TYPE_COMPATIBLE(_x, _y) \
	__builtin_types_compatible_p(typeof(_x), typeof(_y))

#define BUILD_BUG_ON(_cond) \
	_Static_assert(!(_cond), "BUILD_BUG_ON: " #_cond)

static __always_inline __must_check bool __must_check_overflow(bool overflow)
{
	return unlikely(overflow);
}

#define check_add_overflow(_x, _y, _out) \
	__must_check_overflow(__builtin_add_overflow((_x), (_y), (_out)))
#define check_sub_overflow(_x, _y, _out) \
	__must_check_overflow(__builtin_sub_overflow((_x), (_y), (_out)))
#define check_mul_overflow(_x, _y, _out) \
	__must_check_overflow(__builtin_mul_overflow((_x), (_y), (_out)))

#endif

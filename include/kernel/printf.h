#ifndef EDOS_PRINTF_H
#define EDOS_PRINTF_H

#include <arch/types.h>
#include <kernel/result.h>
#include <stdarg.h>

result_t kvsnprintf_c(char *str, size_t size, size_t *out_count,
		      const char *fmt, va_list ap);
result_t ksnprintf_c(char *str, size_t size, size_t *out_count,
		     const char *fmt, ...);

result_t kvsnprintf(char *str, size_t size, const char *fmt, va_list ap);
result_t ksnprintf(char *str, size_t size, const char *fmt, ...);

result_t kvprintf(const char *fmt, va_list ap);
result_t kprintf(const char *fmt, ...);

#endif

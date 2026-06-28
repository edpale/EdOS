#include <kernel/printf.h>
#include <limits.h>

typedef void (*putc_func_t)(int c, void *arg);

static inline void emit_char(putc_func_t putc, void *arg,
			     size_t *count, char c)
{
	putc(c, arg);
	(*count)++;
}

static size_t handle_u64(putc_func_t putc, void *arg, int base, u64 v)
{
	char tmp[64];
	const char *digits = "0123456789abcdef";
	int i = 0;
	size_t count = 0;

	if (v == 0) {
		emit_char(putc, arg, &count, '0');
		return count;
	}
	while (v) {
		tmp[i++] = digits[v % base];
		v /= base;
	}
	while (i--)
		emit_char(putc, arg, &count, tmp[i]);
	return count;
}

static size_t handle_i64(putc_func_t putc, void *arg, i64 v)
{
	size_t count = 0;
	u64 u = (u64)v;

	if (v < 0) {
		emit_char(putc, arg, &count, '-');
		u = -u;
	}
	count += handle_u64(putc, arg, 10, u);
	return count;
}

enum directive_type {
	DIRECTIVE_TYPE_PERC,
	DIRECTIVE_TYPE_UNUM,
	DIRECTIVE_TYPE_NUM,
	DIRECTIVE_TYPE_CHAR,
	DIRECTIVE_TYPE_STR,
	DIRECTIVE_TYPE_PTR,
};

struct directive_spec {
	enum directive_type type;
	size_t size;
	int base;
};

static result_t parse_directive(const char **fmt, struct directive_spec *spec)
{
	bool done;
	unsigned int lcount = 0;
	bool zused = false;

	spec->base = 10;
	spec->size = sizeof(int);

	do {
		done = true;

		switch (*(*fmt)++) {
		case '%':
			spec->type = DIRECTIVE_TYPE_PERC;
			break;

		case 'l':
			if (zused)
				return RES_INVALID_ARG;

			switch (lcount) {
			case 0:
				spec->size = sizeof(long int);
				break;
			case 1:
				spec->size = sizeof(long long int);
				break;
			default:
				return RES_INVALID_ARG;
			}

			lcount++;
			done = false;
			break;

		case 'z':
			if (zused || lcount > 0)
				return RES_INVALID_ARG;

			spec->size = sizeof(size_t);
			zused = true;
			done = false;
			break;

		case 'x':
			spec->type = DIRECTIVE_TYPE_UNUM;
			spec->base = 16;
			break;

		case 'u':
			spec->type = DIRECTIVE_TYPE_UNUM;
			break;

		case 'o':
			spec->type = DIRECTIVE_TYPE_UNUM;
			spec->base = 8;
			break;

		case 'i':
		case 'd':
			spec->type = DIRECTIVE_TYPE_NUM;
			break;

		case 'c':
			if (zused || lcount > 0)
				return RES_INVALID_ARG;

			spec->type = DIRECTIVE_TYPE_CHAR;
			break;

		case 's':
			if (zused || lcount > 0)
				return RES_INVALID_ARG;

			spec->type = DIRECTIVE_TYPE_STR;
			break;

		case 'p':
			if (zused || lcount > 0)
				return RES_INVALID_ARG;

			spec->type = DIRECTIVE_TYPE_PTR;
			break;

		default:
			return RES_INVALID_ARG;
		}
	} while (!done);

	return RES_OK;
}

static result_t kvformat(putc_func_t putc, void *arg, size_t *out_count,
			 const char *fmt, va_list ap)
{
	size_t count = 0;
	char curr;

	while ((curr = *fmt++)) {
		struct directive_spec spec;
		result_t res;

		if (curr != '%') {
			emit_char(putc, arg, &count, curr);
			continue;
		}

		res = parse_directive(&fmt, &spec);
		if (res)
			return res;

		switch (spec.type) {
		case DIRECTIVE_TYPE_PERC:
			emit_char(putc, arg, &count, '%');
			break;

		case DIRECTIVE_TYPE_UNUM: {
			u64 v;

			if (spec.size <= sizeof(unsigned int))
				v = (u64)va_arg(ap, unsigned int);
			else if (spec.size <= sizeof(unsigned long int))
				v = (u64)va_arg(ap, unsigned long int);
			else
				v = (u64)va_arg(ap, unsigned long long int);

			count += handle_u64(putc, arg, spec.base, v);
			break;
		}

		case DIRECTIVE_TYPE_NUM: {
			i64 v;

			if (spec.size <= sizeof(int))
				v = (i64)va_arg(ap, int);
			else if (spec.size <= sizeof(long int))
				v = (i64)va_arg(ap, long int);
			else
				v = (i64)va_arg(ap, long long int);

			count += handle_i64(putc, arg, v);
			break;
		}

		case DIRECTIVE_TYPE_CHAR:
			emit_char(putc, arg, &count, (char)va_arg(ap, int));
			break;

		case DIRECTIVE_TYPE_STR: {
			const char *s = va_arg(ap, const char *);

			if (!s)
				s = "(null)";
			while (*s)
				emit_char(putc, arg, &count, *s++);
			break;
		}

		case DIRECTIVE_TYPE_PTR:
			emit_char(putc, arg, &count, '0');
			emit_char(putc, arg, &count, 'x');
			count += handle_u64(putc, arg, 16,
					    (u64)(uintptr_t)va_arg(ap, void *));
			break;
		}
	}

	if (out_count)
		*out_count = count;
	return RES_OK;
}

struct buffer_sink {
	char *buffer;
	size_t remain;
};

static void buffer_sink_putc(int c, void *arg)
{
	struct buffer_sink *sink = arg;

	if (sink->remain <= 1)
		return;

	*sink->buffer++ = (char)c;
	sink->remain--;
}

result_t kvsnprintf_c(char *str, size_t size, size_t *out_count,
		      const char *fmt, va_list ap)
{
	struct buffer_sink sink = {
		.buffer = str,
		.remain = size,
	};
	result_t res;
	size_t count;

	if (!str && size > 0)
		return RES_INVALID_ARG;

	res = kvformat(buffer_sink_putc, &sink, &count, fmt, ap);

	if (size > 0)
		*sink.buffer = '\0';
	if (out_count)
		*out_count = count;
	if (res == RES_OK && count >= size)
		return RES_TRUNCATED;
	return res;
}

result_t ksnprintf_c(char *str, size_t size, size_t *out_count,
		     const char *fmt, ...)
{
	va_list ap;
	result_t res;

	va_start(ap, fmt);
	res = kvsnprintf_c(str, size, out_count, fmt, ap);
	va_end(ap);
	return res;
}

result_t kvsnprintf(char *str, size_t size, const char *fmt, va_list ap)
{
	return kvsnprintf_c(str, size, NULL, fmt, ap);
}

result_t ksnprintf(char *str, size_t size, const char *fmt, ...)
{
	va_list ap;
	result_t res;

	va_start(ap, fmt);
	res = kvsnprintf(str, size, fmt, ap);
	va_end(ap);
	return res;
}

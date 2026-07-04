#include <kernel/string.h>

void *memmove(void *dest, const void *src, size_t n)
{
	u8 *d = dest;
	const u8 *s = src;

	if (d == s || n == 0)
		return d;

	if (d > s) {
		for (size_t i = n; i > 0; i--)
			d[i - 1] = s[i - 1];
	} else {
		for (size_t i = 0; i < n; i++)
			d[i] = s[i];
	}

	return d;
}

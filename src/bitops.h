#if !defined(BITOPS_H)
#define BITOPS_H

#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#include "compiler.h"

static inline uint8_t rol8(uint8_t value, unsigned int shift)
{
	size_t mask = CHAR_BIT * sizeof(value) - 1;
	return (value << (shift & mask)) | (value >> (-shift & mask));
}

static inline uint16_t rol16(uint16_t value, unsigned int shift)
{
	size_t mask = CHAR_BIT * sizeof(value) - 1;
	return (value << (shift & mask)) | (value >> (-shift & mask));
}

static inline uint32_t rol32(uint32_t value, unsigned int shift)
{
	size_t mask = CHAR_BIT * sizeof(value) - 1;
	return (value << (shift & mask)) | (value >> (-shift & mask));
}

static inline uint64_t rol64(uint64_t value, unsigned int shift)
{
	size_t mask = CHAR_BIT * sizeof(value) - 1;
	return (value << (shift & mask)) | (value >> (-shift & mask));
}

static inline uint8_t ror8(uint8_t value, unsigned int shift)
{
	size_t mask = CHAR_BIT * sizeof(value) - 1;
	return (value >> (shift & mask)) | (value << (-shift & mask));
}

static inline uint16_t ror16(uint16_t value, unsigned int shift)
{
	size_t mask = CHAR_BIT * sizeof(value) - 1;
	return (value >> (shift & mask)) | (value << (-shift & mask));
}

static inline uint32_t ror32(uint32_t value, unsigned int shift)
{
	size_t mask = CHAR_BIT * sizeof(value) - 1;
	return (value >> (shift & mask)) | (value << (-shift & mask));
}

static inline uint64_t ror64(uint64_t value, unsigned int shift)
{
	size_t mask = CHAR_BIT * sizeof(value) - 1;
	return (value >> (shift & mask)) | (value << (-shift & mask));
}

#if __has_builtin(__builtin_clz)
static inline int fls(unsigned int x)
{
	return x ? CHAR_BIT * sizeof(x) - __builtin_clz(x) : 0;
}
#else
static inline int fls(unsigned int x)
{
	int ret = CHAR_BIT * sizeof(x);
	unsigned int mask = ~0u;

	if (!x)
		return 0;

	for (int ii = (ret >> 1); ii; ii >>= 1) {
		mask <<= ii;
		if (!(x & mask)) {
			x <<= ii;
			ret -= ii;
		}
	}
	return ret;
}
#endif /* __has_builtin(__builtin_clz) */

#if __has_builtin(__builtin_clzl)
static inline int flsl(unsigned long x)
{
	return x ? CHAR_BIT * sizeof(x) - __builtin_clzl(x) : 0;
}
#else
static inline int flsl(unsigned long x)
{
	int ret = CHAR_BIT * sizeof(x);
	unsigned long mask = ~0ul;

	if (!x)
		return 0;

	for (int ii = (ret >> 1); ii; ii >>= 1) {
		mask <<= ii;
		if (!(x & mask)) {
			x <<= ii;
			ret -= ii;
		}
	}
	return ret;
}
#endif /* __has_builtin(__builtin_clzl) */

#if __has_builtin(__builtin_ffs)
static inline int ffs(unsigned int x)
{
	return __builtin_ffs(x);
}
#else
static inline int ffs(unsigned int x)
{
	int ret = 1;
	unsigned int mask = ~0u;
	size_t size = CHAR_BIT * sizeof(x);

	if (!x)
		return 0;

	for (int ii = (size >> 1); ii; ii >>= 1) {
		mask >>= ii;
		if (!(x & mask)) {
			x >>= ii;
			ret += ii;
		}
	}
	return ret;
}
#endif /* __has_builtin(__builtin_ffs) */

#if __has_builtin(__builtin_ffsl)
static inline int ffsl(unsigned long x)
{
	return __builtin_ffsl(x);
}
#else
static inline int ffsl(unsigned long x)
{
	int ret = 1;
	unsigned long mask = ~0ul;
	size_t size = CHAR_BIT * sizeof(x);

	if (!x)
		return 0;

	for (int ii = (size >> 1); ii; ii >>= 1) {
		mask >>= ii;
		if (!(x & mask)) {
			x >>= ii;
			ret += ii;
		}
	}
	return ret;
}
#endif /* __has_builtin(__builtin_ffsl) */

#endif /* !defined(BITOPS_H) */

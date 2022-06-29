#if !defined(UTIL_H)
#define UTIL_H

#include <stdbool.h>
#include <stddef.h>

#include "compiler.h"
#include "bitops.h"

#define array_len(x)	(sizeof(x) / sizeof((x)[0]))

#define container_of(ptr, type, field) \
	((type *)((char *)(ptr) - offsetof(type, field)))

#if __has_builtin(__builtin_popcountl)
static inline bool is_pow2(unsigned long x)
{
	return __builtin_popcountl(x) == 1;
}
#else
static inline bool is_pow2(unsigned long x)
{
	return x && !(x & (x - 1));
}
#endif /* __has_builtin(__builtin_popcountl) */

static inline unsigned long round_up_pow2(unsigned long x)
{
	return 1ul << flsl(x - 1);
}

static inline unsigned long round_down_pow2(unsigned long x)
{
	return 1ul << (flsl(x) - 1);
}

#endif /* !defined(UTIL_H) */

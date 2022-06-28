#if !defined(BYTEORDER_H)
#define BYTEORDER_H

#include <stdint.h>

#include "compiler.h"

#if defined(__BYTE_ORDER__)
#  if (defined(__ORDER_LITTLE_ENDIAN__) && \
       (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__))
#    define HOST_LITTLE_ENDIAN	1
#    define HOST_BIG_ENDIAN	0
#  elif (defined(__ORDER_BIG_ENDIAN__) && \
	 (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__))
#    define HOST_LITTLE_ENDIAN	0
#    define HOST_BIG_ENDIAN	1
#  endif /* __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__ */
#elif (defined(__LITTLE_ENDIAN__) && (__LITTLE_ENDIAN__ == 1)) || \
	(defined(__LITTLE_ENDIAN) && (__LITTLE_ENDIAN == 1))
#  define HOST_LITTLE_ENDIAN	1
#  define HOST_BIG_ENDIAN	0
#elif (defined(__BIG_ENDIAN__) && (__BIG_ENDIAN__ == 1)) || \
	(defined(__BIG_ENDIAN) && (__BIG_ENDIAN == 1))
#  define HOST_LITTLE_ENDIAN	0
#  define HOST_BIG_ENDIAN	1
#endif /* defined(__BYTE_ORDER__) */

#if defined(HOST_LITTLE_ENDIAN)
static always_inline int host_is_little_endian(void)
{
	return HOST_LITTLE_ENDIAN;
}

static always_inline int host_is_big_endian(void)
{
	return HOST_BIG_ENDIAN;
}
#else
static inline int host_is_little_endian(void)
{
	const union {
		uint32_t word;
		uint8_t byte[4];
	} x = { .word = 1 };

	return x.byte[0];
}

static inline int host_is_big_endian(void)
{
	const union {
		uint32_t word;
		uint8_t byte[4];
	} x = { .word = 1 };

	return x.byte[3];
}
#endif /* defined(HOST_LITTLE_ENDIAN) */

#endif /* !defined(BYTEORDER_H) */

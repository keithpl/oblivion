#if !defined(UNALIGNED_H)
#define UNALIGNED_H

#include <stdint.h>
#include <string.h>

#include "compiler.h"
#include "byteops.h"

#if __has_attribute(__packed__)

#define packed_u16 packed_u16
#define packed_u32 packed_u32
#define packed_u64 packed_u64

typedef struct { pack_field uint16_t value; } packed_u16;
typedef struct { pack_field uint32_t value; } packed_u32;
typedef struct { pack_field uint64_t value; } packed_u64;

static inline uint16_t get_unaligned_u16(const void *ptr)
{
	const packed_u16 *packed = ptr;
	return packed->value;
}

static inline uint32_t get_unaligned_u32(const void *ptr)
{
	const packed_u32 *packed = ptr;
	return packed->value;
}

static inline uint64_t get_unaligned_u64(const void *ptr)
{
	const packed_u64 *packed = ptr;
	return packed->value;
}

static inline void put_unaligned_u16(void *ptr, uint16_t value)
{
	packed_u16 *packed = ptr;
	packed->value = value;
}

static inline void put_unaligned_u32(void *ptr, uint32_t value)
{
	packed_u32 *packed = ptr;
	packed->value = value;
}

static inline void put_unaligned_u64(void *ptr, uint64_t value)
{
	packed_u64 *packed = ptr;
	packed->value = value;
}

#else /* __has_attribute(__packed__) */

static inline uint16_t get_unaligned_u16(const void *ptr)
{
	uint16_t value;

	memcpy(&value, ptr, sizeof(value));
	return value;
}

static inline uint32_t get_unaligned_u32(const void *ptr)
{
	uint32_t value;

	memcpy(&value, ptr, sizeof(value));
	return value;
}

static inline uint64_t get_unaligned_u64(const void *ptr)
{
	uint64_t value;

	memcpy(&value, ptr, sizeof(value));
	return value;
}

static inline void put_unaligned_u16(void *ptr, uint16_t value)
{
	memcpy(ptr, &value, sizeof(value));
}

static inline void put_unaligned_u32(void *ptr, uint32_t value)
{
	memcpy(ptr, &value, sizeof(value));
}

static inline void put_unaligned_u64(void *ptr, uint64_t value)
{
	memcpy(ptr, &value, sizeof(value));
}

#endif /* __has_attribute(__packed__) */

static inline uint16_t get_unaligned_le16(const void *ptr)
{
	return host_to_le16(get_unaligned_u16(ptr));
}

static inline uint32_t get_unaligned_le32(const void *ptr)
{
	return host_to_le32(get_unaligned_u32(ptr));
}

static inline uint64_t get_unaligned_le64(const void *ptr)
{
	return host_to_le64(get_unaligned_u64(ptr));
}

static inline uint16_t get_unaligned_be16(const void *ptr)
{
	return host_to_be16(get_unaligned_u16(ptr));
}

static inline uint32_t get_unaligned_be32(const void *ptr)
{
	return host_to_be32(get_unaligned_u32(ptr));
}

static inline uint64_t get_unaligned_be64(const void *ptr)
{
	return host_to_be64(get_unaligned_u64(ptr));
}

static inline void put_unaligned_le16(void *ptr, uint16_t value)
{
	put_unaligned_u16(ptr, host_to_le16(value));
}

static inline void put_unaligned_le32(void *ptr, uint32_t value)
{
	put_unaligned_u32(ptr, host_to_le32(value));
}

static inline void put_unaligned_le64(void *ptr, uint64_t value)
{
	put_unaligned_u64(ptr, host_to_le64(value));
}

static inline void put_unaligned_be16(void *ptr, uint16_t value)
{
	put_unaligned_u16(ptr, host_to_be16(value));
}

static inline void put_unaligned_be32(void *ptr, uint32_t value)
{
	put_unaligned_u32(ptr, host_to_be32(value));
}

static inline void put_unaligned_be64(void *ptr, uint64_t value)
{
	put_unaligned_u64(ptr, host_to_be64(value));
}

#endif /* !defined(UNALIGNED_H) */

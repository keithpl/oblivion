#if !defined(MINMAX_H)
#define MINMAX_H

#define minmax_generic(op, x, y)	\
_Generic((x) + (y),			\
	int:		op ## _int,	\
	long:		op ## _long,	\
	unsigned int:	op ## _uint,	\
	unsigned long:	op ## _ulong,	\
	float:		op ## _float,	\
	double:		op ## _double,	\
	long double:	op ## _ldouble	\
)((x), (y))

#define min(x, y)	minmax_generic(min, (x), (y))
#define max(x, y)	minmax_generic(max, (x), (y))

#define min3(x, y, z)	min(min((x), (y)), (z))
#define max3(x, y, z)	max(max((x), (y)), (z))

static inline int min_int(int x, int y)
{
	return (x < y) ? x : y;
}

static inline int max_int(int x, int y)
{
	return (x > y) ? x : y;
}

static inline long min_long(long x, long y)
{
	return (x < y) ? x : y;
}

static inline long max_long(long x, long y)
{
	return (x > y) ? x : y;
}

static inline unsigned int min_uint(unsigned int x, unsigned int y)
{
	return (x < y) ? x : y;
}

static inline unsigned int max_uint(unsigned int x, unsigned int y)
{
	return (x > y) ? x : y;
}

static inline unsigned long min_ulong(unsigned long x, unsigned long y)
{
	return (x < y) ? x : y;
}

static inline unsigned long max_ulong(unsigned long x, unsigned long y)
{
	return (x > y) ? x : y;
}

static inline float min_float(float x, float y)
{
	return (x < y) ? x : y;
}

static inline float max_float(float x, float y)
{
	return (x > y) ? x : y;
}

static inline double min_double(double x, double y)
{
	return (x < y) ? x : y;
}

static inline double max_double(double x, double y)
{
	return (x > y) ? x : y;
}

static inline long double min_ldouble(long double x, long double y)
{
	return (x < y) ? x : y;
}

static inline long double max_ldouble(long double x, long double y)
{
	return (x > y) ? x : y;
}

#endif /* !defined(MINMAX_H) */

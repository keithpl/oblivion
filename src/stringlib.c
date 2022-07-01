#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>

#include "compiler.h"
#include "stringlib.h"

int vscnprintf(char *restrict s, size_t n, const char *restrict format,
	       va_list args)
{
	int ret;
	long ssize = n;

	if (!n)
		return 0;

	ret = vsnprintf(s, n, format, args);
	if (ret < ssize)
		return ret;

	return n - 1;
}

int scnprintf(char *restrict s, size_t n, const char *restrict format, ...)
{
	int ret;
	va_list args;

	va_start(args, format);
	ret = vscnprintf(s, n, format, args);
	va_end(args);

	return ret;
}

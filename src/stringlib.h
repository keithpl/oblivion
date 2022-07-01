#if !defined(STRINGLIB_H)
#define STRINGLIB_H

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>

#include "compiler.h"

int vscnprintf(char *restrict s, size_t n, const char *restrict format,
	       va_list args) format_vprintf(3);

int scnprintf(char *restrict s, size_t n, const char *restrict format, ...)
	format_printf(3);

#endif /* !defined(STRINGLIB_H) */

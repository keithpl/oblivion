#include <ctype.h>
#include <stdarg.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

bool sglob(const char *mask, const char *text)
{
	const char *bt_mask = NULL;
	const char *bt_text = NULL;

	while (1) {
		const char mc = *mask++;
		const char tc = *text++;

		switch (mc) {
		case '?':
			if (!tc)
				return false;

			break;
		case '*':
			if (!*mask)
				return true;

			bt_mask = mask;
			bt_text = --text;
			break;
		default:
			if (mc == tc) {
				if (!mc)
					return true;

				break;
			}

			if (!tc || !bt_mask)
				return false;

			mask = bt_mask;
			text = ++bt_text;
			break;
		}
	}
}

bool scaseglob(const char *mask, const char *text)
{
	const unsigned char *bt_umask = NULL;
	const unsigned char *bt_utext = NULL;
	const unsigned char *umask = (const unsigned char *)mask;
	const unsigned char *utext = (const unsigned char *)text;

	while (1) {
		const unsigned char mc = *umask++;
		const unsigned char tc = *utext++;

		switch (mc) {
		case '?':
			if (!tc)
				return false;

			break;
		case '*':
			if (!*umask)
				return true;

			bt_umask = umask;
			bt_utext = --utext;
			break;
		default:
			if (tolower(mc) == tolower(tc)) {
				if (!mc)
					return true;

				break;
			}

			if (!tc || !bt_umask)
				return false;

			umask = bt_umask;
			utext = ++bt_utext;
			break;
		}
	}
}

int scasecmp(const char *s1, const char *s2)
{
	int c1, c2;
	const unsigned char *us1 = (const unsigned char *)s1;
	const unsigned char *us2 = (const unsigned char *)s2;

	if (s1 == s2)
		return 0;

	do {
		c1 = tolower(*us1++);
		c2 = tolower(*us2++);
	} while (c1 && (c1 == c2));

	return c1 - c2;
}

int sncasecmp(const char *s1, const char *s2, size_t n)
{
	int c1, c2;
	const unsigned char *us1 = (const unsigned char *)s1;
	const unsigned char *us2 = (const unsigned char *)s2;

	if (!n || (s1 == s2))
		return 0;

	do {
		c1 = tolower(*us1++);
		c2 = tolower(*us2++);
	} while (--n && c1 && (c1 == c2));

	return c1 - c2;
}

size_t snlen(const char *s, size_t n)
{
	const char *end;

	end = memchr(s, 0, n);
	if (end)
		return end - s;

	return n;
}

void *mdup(const void *p, size_t n)
{
	void *ret;

	ret = malloc(n);
	if (ret)
		memcpy(ret, p, n);

	return ret;
}

char *sdup(const char *s)
{
	return mdup(s, strlen(s) + 1);
}

char *sndup(const char *s, size_t n)
{
	char *ret;

	n = snlen(s, n);
	ret = malloc(n + 1);
	if (ret) {
		memcpy(ret, s, n);
		ret[n] = 0;
	}

	return ret;
}

size_t sncpy(char *restrict dest, const char *restrict src, size_t n)
{
	size_t len;

	if (!n)
		return 0;

	len = snlen(src, n - 1);
	memcpy(dest, src, len);
	dest[len] = 0;
	return len;
}

size_t szcpy(char *restrict dest, const char *restrict src, size_t n)
{
	size_t len;

	len = sncpy(dest, src, n);
	memset(dest + len, 0, n - len);
	return len;
}

char *ssep(char **restrict pstr, const char *restrict delim)
{
	char *end;
	char *str = *pstr;

	if (!str)
		return NULL;

	end = str + strcspn(str, delim);
	if (*end)
		*end++ = 0;
	else
		end = NULL;

	*pstr = end;
	return str;
}

char *stok(char **restrict pstr, const char *restrict delim)
{
	char *str = *pstr;

	if (!str)
		return NULL;

	str += strspn(str, delim);
	if (!*str)
		return NULL;

	*pstr = str;
	return ssep(pstr, delim);
}

size_t svsplit(char *dest[], char *src, size_t dest_size)
{
	char *tok;
	size_t pos = 0;

	while (pos < dest_size) {
		tok = stok(&src, " ");
		if (!tok)
			break;

		dest[pos++] = tok;
	}
	return pos;
}

size_t svsplit_irc(char *dest[], char *src, size_t dest_size)
{
	char *tok;
	size_t pos = 0;

	while (pos < dest_size) {
		tok = stok(&src, " ");
		if (!tok)
			break;

		dest[pos++] = tok;
		if (src && (*src == ':')) {
			if (pos < dest_size)
				dest[pos++] = src + 1;

			break;
		}
	}
	return pos;
}

size_t svunsplit(char *dest, size_t dest_size, char *src[], size_t src_size)
{
	size_t pos = 0;

	if (!src_size)
		return 0;

	while (1) {
		pos += sncpy(dest + pos, *src++, dest_size - pos);
		if (--src_size && (pos < dest_size))
			dest[pos++] = ' ';
		else
			return pos;
	}
}

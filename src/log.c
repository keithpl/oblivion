#define _POSIX_C_SOURCE 200809L

#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#include "compiler.h"
#include "log.h"

#define LOG_TIMESTAMP_MAXLEN	32
#define LOG_METADATA_MAXLEN	128
#define LOG_ERRSTR_MAXLEN	128
#define LOG_TEXT_MAXLEN		512

struct log_entry {
	int level;
	int errnum;
	int line;
	const char *file;

	char timestamp[LOG_TIMESTAMP_MAXLEN];
	char metadata[LOG_METADATA_MAXLEN];
	char errstr[LOG_ERRSTR_MAXLEN];
	char text[LOG_TEXT_MAXLEN];
};

static FILE *log_file;
static const char *log_path = "oblivion.log";

int log_init(void)
{
	log_file = fopen(log_path, "a+");
	if (!log_file) {
		log_error("Failed to open log file %s", log_path);
		return -1;
	}

	return 0;
}

void log_cleanup(void)
{
	fclose(log_file);
	log_file = NULL;
}

static inline const char *log_level2str(int level)
{
	switch (level) {
	case LOG_TRACE: return "TRACE";
	case LOG_DEBUG: return "DEBUG";
	case LOG_INFO: return "INFO";
	case LOG_WARN: return "WARN";
	case LOG_ERROR: return "ERROR";
	case LOG_FATAL: return "FATAL";
	default: return "INVAL";
	}
}

static void log_timestamp(struct log_entry *entry)
{
	size_t ret;
	time_t now;
	struct tm tm;

	time(&now);
	if (!localtime_r(&now, &tm)) {
		fprintf(stderr, "localtime_r() failed to transform time.\n");
		return;
	}

	ret = strftime(entry->timestamp, sizeof(entry->timestamp),
		       "%Y-%m-%d %H:%M:%S", &tm);
	if (!ret)
		fprintf(stderr, "strftime() failed to format time.\n");
}

static void log_metadata(struct log_entry *entry)
{
	const char *level_str;

	level_str = log_level2str(entry->level);
	snprintf(entry->metadata, sizeof(entry->metadata), "%-5s %s:%d",
		 level_str, entry->file, entry->line);
}

static inline void log_strerror(struct log_entry *entry)
{
	strerror_r(entry->errnum, entry->errstr, sizeof(entry->errstr));
}

static inline void log_write(const struct log_entry *entry)
{
	fprintf(stderr, "%s %s %s\n", entry->timestamp, entry->metadata,
		entry->text);

	if (log_file) {
		fprintf(log_file, "%s %s %s\n", entry->timestamp,
			entry->metadata, entry->text);
	}
}

static inline void log_write_errnum(const struct log_entry *entry)
{
	fprintf(stderr, "%s %s %s [errno: %s]\n", entry->timestamp,
		entry->metadata, entry->text, entry->errstr);

	if (log_file) {
		fprintf(log_file, "%s %s %s [errno: %s]\n", entry->timestamp,
			entry->metadata, entry->text, entry->errstr);
	}
}

static void log_vprintf(struct log_entry *entry, const char *restrict format,
			va_list args) format_vprintf(2);

static void log_vprintf(struct log_entry *entry,
			const char *restrict format, va_list args)
{
	int ret;

	log_timestamp(entry);
	log_metadata(entry);

	ret = vsnprintf(entry->text, sizeof(entry->text), format, args);
	if (ret < 1) {
		fprintf(stderr, "Failed to format log entry.\n");
		return;
	}

	if (!entry->errnum) {
		log_write(entry);
	} else {
		log_strerror(entry);
		log_write_errnum(entry);
	}
}

void log_entry(int level, const char *restrict file, int line,
	       const char *restrict format, ...)
{
	va_list args;
	struct log_entry entry = {
		.level = level,
		.errnum = errno,
		.file = file,
		.line = line
	};

	va_start(args, format);
	log_vprintf(&entry, format, args);
	va_end(args);
}

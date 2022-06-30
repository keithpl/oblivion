#if !defined(LOG_H)
#define LOG_H

#include "compiler.h"

enum log_level {
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL
};

#define log_printf(level, ...) \
	log_entry(level, __FILE__, __LINE__, __VA_ARGS__)

#define log_trace(...)	log_printf(LOG_TRACE, __VA_ARGS__)
#define log_debug(...)	log_printf(LOG_DEBUG, __VA_ARGS__)
#define log_info(...)	log_printf(LOG_INFO, __VA_ARGS__)
#define log_warn(...)	log_printf(LOG_WARN, __VA_ARGS__)
#define log_error(...)	log_printf(LOG_ERROR, __VA_ARGS__)
#define log_fatal(...)	log_printf(LOG_FATAL, __VA_ARGS__)

int log_init(void);
void log_cleanup(void);

void log_entry(int level, const char *restrict file, int line,
	       const char *restrict format, ...) format_printf(4);

#endif /* !defined(LOG_H) */

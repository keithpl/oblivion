#if !defined(LOG_H)
#define LOG_H

enum log_level {
	LOG_TRACE,
	LOG_DEBUG,
	LOG_INFO,
	LOG_WARN,
	LOG_ERROR,
	LOG_FATAL
};

#define log_trace(...)
#define log_debug(...)
#define log_info(...)
#define log_warn(...)
#define log_error(...)
#define log_fata(...)

#endif /* !defined(LOG_H) */

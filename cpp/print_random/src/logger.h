#include <iostream>
#include <stdarg.h>

#define UINT_TEST 0

enum LogLevel {
    LOG_DEBUG = 0,
    LOG_INFO,
    LOG_WARN,
    LOG_ERR,
    LOG_MAX,
};

class Logger {
    private:
        enum LogLevel m_level;
    public:
        Logger(enum LogLevel level) { m_level = level; };
        Logger() { m_level = LOG_DEBUG; };
        ~Logger() { m_level = LOG_MAX; };
        int Log(enum LogLevel level, const char *format, ...);
};

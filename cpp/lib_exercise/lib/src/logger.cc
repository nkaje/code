#include <iostream>
#include <stdarg.h>
#include "logger.h"

int Logger::Log(enum LogLevel level, const char *format, ...)
{
    if (level >= m_level) {
        va_list args;
        va_start (args, format);
        vprintf(format, args);
        va_end(args);
    }
    return 0;
}


#if UNIT_TEST
int main()
{
    Logger Logger(gLogLevel);
    std::string LogMessage = "Test";

    Logger.Log(LOG_DEBUG, "DEBUG 0x%d", 0);
    return 0;
}
#endif

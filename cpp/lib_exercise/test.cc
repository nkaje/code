#include <iostream>
#include <logger.h>

int main()
{
    Logger logger(LOG_DEBUG);
    std::string LogMessage = "Test";

    logger.Log(LOG_DEBUG, "DEBUG %d\n", 0);
    return 0;
}

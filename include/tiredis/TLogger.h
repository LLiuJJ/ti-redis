#include <Poco/Logger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/AutoPtr.h>
#include <string>

enum LogDest
{
    logConsole = 0x01 << 0,
    logFILE = 0x01 << 1,
};

class LogManager
{
public:

    static LogManager& Instance();

    ~LogManager();

    Poco::Logger& CreateLog(unsigned int dest = logConsole,
                            const char* pDir = 0);

    Poco::Logger& Log();

private:

    LogManager();

};

extern Poco::Logger& g_log;

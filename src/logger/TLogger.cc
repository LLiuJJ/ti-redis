#include <tiredis/TLogger.h>
#include <Poco/ConsoleChannel.h>
#include <Poco/SimpleFileChannel.h>
#include <Poco/SplitterChannel.h>
#include <Poco/AutoPtr.h>

using Poco::Logger;
using Poco::SimpleFileChannel;
using Poco::SplitterChannel;
using Poco::ConsoleChannel;
using Poco::AutoPtr;

LogManager& LogManager::Instance()
{
    static LogManager mgr;
    return mgr;
}

LogManager::LogManager()
{
}

LogManager::~LogManager()
{
}

Poco::Logger& LogManager::CreateLog(unsigned int dest, const char* pDir)
{
    if (dest & logConsole) {
        AutoPtr<ConsoleChannel> pChannel(new ConsoleChannel);
        Poco::Logger::root().setChannel(pChannel);
        return Poco::Logger::root();
    } 
    else
    {
        AutoPtr<ConsoleChannel> cChannel(new ConsoleChannel);
        AutoPtr<SimpleFileChannel> fChannel(new SimpleFileChannel);
        AutoPtr<SplitterChannel> pSC(new SplitterChannel);
        std::string logPath = pDir ? pDir : ".";
        fChannel->setProperty("path", logPath);
        fChannel->setProperty("rotation", "2 K");
        pSC->addChannel(cChannel);
        pSC->addChannel(fChannel);
        Logger::root().setChannel(pSC);
        return Poco::Logger::root();
    }    
}
 
Poco::Logger& LogManager::Log()
{
    return Poco::Logger::root();
}


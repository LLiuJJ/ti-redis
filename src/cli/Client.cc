#include <tiredis/Client.h>
#include <tiredis/TLogger.h>
#include <tiredis/UnboundedBuffer.h>

PacketLength Client::_HandlePacket(const char* start, std::size_t bytes)
{
    const char* const end   = start + bytes;
    const char* ptr  = start;
    // deal with packet
    std::string cCmd(start, bytes);
    LogManager::Instance().Log().information(cCmd);

    reply_.PushData("+OK\r\n", 5);
    SendPacket(reply_);
    return static_cast<PacketLength>(cCmd.length());   
}

Client::Client()
{
    _Reset();
}

void Client::_Reset()
{
    reply_.Clear();
}

void Client::OnConnect()
{

}
